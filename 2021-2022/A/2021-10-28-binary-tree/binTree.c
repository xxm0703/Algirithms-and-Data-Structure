#include <stdlib.h>
#include <stdio.h>

typedef struct node_t {
	int value;
	struct node_t *left, *right;
	unsigned char level;
} node_t;

node_t *add(node_t *root, int value) {
	// dyno
	if (root == NULL) {
		node_t *newNode = (node_t *)malloc(sizeof(node_t));
		newNode->left = NULL;
		newNode->right = NULL;
		newNode->value = value;
		return newNode;
	}

	if (value < root->value) 
		root->left = add(root->left, value);
	
	else if (value > root->value) 
		root->right = add(root->right, value);
	
	return root;
}

unsigned char _height(node_t *node, unsigned char level) {
	if (node == NULL)
		return level;

	unsigned char right =  _height(node->right, level + 1);
	unsigned char left = _height(node->left, level + 1);
	
	return right > left ? right : left;
}

unsigned char height(node_t *root) {
	
	return _height(root, 0);
}

void printTree(node_t *root) {
	if (root == NULL)
		return; 
	
	printf("%d\n", root->value);
	unsigned short pos = 0;

	printf("\n");
}


int main() {
	node_t *root = add(NULL, 15); 
	root = add(root, 11);
	root = add(root, 8);
	root = add(root, -2);
	root = add(root, 20);

	printf("%hhu\n", height(root));
	//printTree(root);
	return 0;
}


