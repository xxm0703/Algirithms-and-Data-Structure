#pragma once
#include <stdlib.h>


struct list_node_t {
  void* value;
  struct list_node_t* next;
};

struct list_node_t* init_list_node(void* value) {
  struct list_node_t* new_node = malloc(sizeof(struct list_node_t));

  new_node->value = value;
  new_node->next = NULL;

  return new_node;
}

struct list_node_t* add_to_list(struct list_node_t* list, void* value) {
  struct list_node_t* new_node = init_list_node(value);

  new_node->next = list;

  return new_node;
}

int has_in_list(struct list_node_t* list, void* value) {
  for(struct list_node_t* curr = list; curr != NULL; curr = curr->next) {
    if(curr->value == value) return 1;
  }

  return 0;
}

struct list_node_t* remove_from_list(struct list_node_t* list, void* value) {
  if(list == NULL) return list;

  struct list_node_t* tmp = list;
  struct list_node_t* prev = NULL;

  // Find the correct node
  while(tmp != NULL && tmp->value != value) {
    prev = tmp;
    tmp = tmp->next;
  }

  // Not found
  if(tmp == NULL) return list;

  // If prev == NULL then tmp is the first node
  if(prev == NULL) {
    list = tmp->next;
  } else {
    // Else it's somewhere inside the list
    prev->next = tmp->next;
  }

  free(tmp);

  return list;
}

