#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char charCipherN(char c, unsigned short n) {
	size_t alphaLen = 'z' - 'a' + 1;
	
	return c + n;	
}

char charDecipherN(char c, unsigned short n) {
	size_t alphaLen = 'z' - 'a' + 1;
	
	return c - n;	
}

void cipherN(char *str, size_t len, unsigned short n) {
	for (size_t i = 0; i < len; ++i) {
		str[i] = charCipherN(str[i], n);
	}
}

void cipher(char *str) {
	cipherN(str, strlen(str) , 1);
}

void decipherN(char *str, size_t len, unsigned short n) {
	size_t alphaLen = 'z' - 'a' + 1;
	for (size_t i = 0; i < len; ++i) {
		str[i] = charDecipherN(str[i], n);
	}
}

size_t keyToNum(char *key) {
	size_t n = 0;
	size_t len = strlen(key);
	for (size_t i = 0; i < len; i++)
		n += key[i];
	return n;
}

void CBC(char *str, char *key, char **v) {
        size_t strLen = strlen(str);
	size_t vLen = strlen(*v);
	for (size_t i = 0; i < strLen; ++i) {
		str[i] = str[i] ^ (*v)[i % vLen];
	}
	
	cipherN(str, strLen, keyToNum(key));
	
	free(*v);
	*v = strdup(str);
}


void DeCBC(char *str, size_t len, char *key, char **v, size_t vLen) {
	char *tempVect = (char *)malloc(sizeof(char) * (len + 5));
	memcpy(tempVect, str, len + 1);
	decipherN(str, len, keyToNum(key));
	
	for (size_t i = 0; i < len; ++i) {
		str[i] = str[i] ^ (*v)[i % vLen];
	}
		
	free(*v);
	*v = tempVect;
}

int main() {

	char str[] = "deseti a za shumni";
	char *v_c = strdup("vec");
	char *v_d = strdup("vec");
	char key[] = "kluch";

	printf("%s - %s\n", str, v_c);
	CBC(str, key, &v_c);
	printf("%s - %s - %s\n", str, v_c, v_d);
	DeCBC(str, strlen(str), key, &v_d, 3);
	printf("%s - %s\n", str, v_d);
	return 0;
}


