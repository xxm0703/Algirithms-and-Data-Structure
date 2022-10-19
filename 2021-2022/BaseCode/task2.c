#include <stdlib.h>
#include <stdbool.h>

struct node_t {
    char data;
    struct node_t *smaller, *bigger;
};

struct node_t *add(struct node_t *root, int data) {
	if (root == NULL) {
		struct node_t *newNode = (struct node_t *)malloc(sizeof(struct node_t));
		newNode->smaller = NULL;
		newNode->bigger = NULL;
		newNode->data = data;
		return newNode;
	}

	if (data < root->data) 
		root->smaller = add(root->smaller, data);
	
	else if (data > root->data) 
		root->bigger = add(root->bigger, data);
	
	return root;
}

// WRITE AFTER THIS COMMENT

bool has_snare(struct node_t *root);