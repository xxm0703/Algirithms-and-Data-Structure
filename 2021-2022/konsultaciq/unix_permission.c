#include<stdio.h>

typedef struct file_t {
	char name[20];
	int user_id;
	int group_id;
	unsigned short permissions;
} file_t;

/*
 	up = 0...0(110)000000000	
 	gp = 0...00001001000(100)	&
			0000(111)	
	op = 0...00000000000(000)
 	fp = 00..000000(110)(010)
 	pm = 00000.00000000(101)
 */
int check_permissions(file_t file, int user_id, int group_id, int permissions_mask) {
	
	permissions_mask &= 7; // Cleaning the mask 010...(***) => 000...(***)
	
	if (user_id == file.user_id) {
		return ((file.permissions >> 6) & permissions_mask) == permissions_mask;
	}
	
	if (group_id == file.group_id) {	
		return ((file.permissions >> 3) & permissions_mask) == permissions_mask;
	}

	return (file.permissions & permissions_mask) == permissions_mask;
}

void set_permissions(file_t *file, int user_permissions, int group_permissions, int other_permissions) {
	int perm = 0;
	perm |= ((user_permissions & 7) << 6);
	perm = perm | ((group_permissions & 7) << 3);
	perm |= (other_permissions & 7);

	file->permissions = perm;
}


int main() {
	file_t f = {"image.jpg", 8, 3, 0};  // 111 001 000 0x1C8 
	set_permissions(&f, 7, 1, 0);	//     101
	printf("%x\n", f.permissions);
	printf("%d\n", check_permissions(f, 8, 1, 5));
	printf("%d\n", check_permissions(f, 3, 3, 1));
	printf("%d\n", check_permissions(f, 1, 1, 1));
	return 0;
}








