#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct node_t {
	int value;
	struct node_t *left, *right;
	unsigned char level;
};

typedef struct node_t node_t;

node_t *add(node_t *root, int value) {
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

node_t *nearestAncestor(node_t *root, int val1, int val2) {
	if (val1 > val2)
		return nearestAncestor(root, val2, val1);

	if (root->value >= val1 && root->value <= val2)
		return root;

	if (root->value > val2)
		return nearestAncestor(root->left, val1, val2);

	return nearestAncestor(root->right, val1, val2);
}

size_t distanceFromRoot(node_t *root, node_t *node) {
	if (root == node)
	    return 0;
	if (root->value > node->value)
	    return 1 + distanceFromRoot(root->left, node);

    return 1 + distanceFromRoot(root->right, node); 
}

size_t distanceFromRootIter(node_t *root, node_t *node) {
    node_t *temp = root;
    size_t dist = 0;
    
    while (temp != node)
    {
        dist++;
        if (root->value > node->value)
    	    temp = temp->left;
        else
    	    temp = temp->right;
    }
    
    return dist;
}


int get_shortest_distance(node_t *root, node_t *a, node_t *b) {
    node_t *commonParent = nearestAncestor(root, a->value, b->value);
    
    return distanceFromRoot(commonParent, a) + distanceFromRoot(commonParent, b);
}




