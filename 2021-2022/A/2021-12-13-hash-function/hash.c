#include<stdio.h>
#include<stdlib.h>

struct pair {
	char *key;
	unsigned short value;
	struct pair *next;
};

struct hash_table {
	struct pair *buckets;
	size_t size;
};

int hash(char *str) {
	return str[0];
}

struct hash_table *init(size_t bucketsCount) {
	struct hash_table *ht = (struct hash_table *)malloc(sizeof(struct hash_table));	
	ht->size = bucketsCount;
	ht->buckets = (struct pair *)calloc(sizeof(struct pair), bucketsCount);
	return ht;
}

int main() {


}





