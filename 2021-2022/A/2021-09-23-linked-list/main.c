#include"linked_list.h"

int main() {
	list_t *l = init_list();
	push(l, 5);		// {5}
	rpush(l, -3); 	// {5, -3}
	rpush(l, 13);	// {5, -3, 13}
	push(l, 43); 	// {43, 5, -3, 13}
	printList(*l);
	pop(l);			// {5, -3, 13}
	printList(*l);
	reverse(l);		// {13, -3, 5}
	printList(*l);
	destroy_list(l);
	return 0;
}
