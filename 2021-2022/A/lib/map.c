#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lib/list.h"
#include "../lib/map.h"

#define BUCKET_COUNT 20

struct map_node_t {
  char* key;
  void* value;
};

struct map_t {
  struct list_node_t** buckets;
  int count;
};

struct map_t* init_map() {
  struct map_t* new_map = malloc(sizeof(struct map_t));

  // Allocate and array of pointers and set them to NULL
  new_map->buckets = calloc(BUCKET_COUNT, sizeof(struct list_node_t*));
  new_map->count = 0;

  return new_map;
}

unsigned int hash_func(char* key) {
  unsigned int result = 1;

  for(int i = 0; i < strlen(key); i++) {
    result *= key[i] * (i + 1);
  }

  return result;
}

void add_to_map(struct map_t* map, char* key, short value) {
  unsigned int bucket_index = hash_func(key) % BUCKET_COUNT;

  if(has_in_map(map, key)) {
    // Find the node and update the value
    for(struct list_node_t* curr = map->buckets[bucket_index]; curr != NULL; curr = curr->next) {
      struct map_node_t* map_node = curr->value;
      if(strcmp(map_node->key, key) == 0) {
        map_node->value = value;
        return;
      }
    }
  }

  // Create and add a new node
  struct map_node_t* new_map_node = malloc(sizeof(struct map_node_t));
  new_map_node->key = malloc(strlen(key) + 1);
  strcpy(new_map_node->key, key);
  new_map_node->value = value;

  map->buckets[bucket_index] = add_to_list(map->buckets[bucket_index], new_map_node);
  map->count++;
}

int has_in_map(struct map_t* map, char* key) {
  unsigned int bucket_index = hash_func(key) % BUCKET_COUNT;

  if(map->buckets[bucket_index] == NULL) return 0;

  for(struct list_node_t* curr = map->buckets[bucket_index]; curr != NULL; curr = curr->next) {
    struct map_node_t* map_node = curr->value;
    if(strcmp(map_node->key, key) == 0) return 1;
  }

  return 0;
}

void remove_from_map(struct map_t* map, char* key) {
  if(map->count <= 0) return;
  if(!has_in_map(map, key)) return;

  unsigned int bucket_index = hash_func(key) % BUCKET_COUNT;
  struct list_node_t* bucket = map->buckets[bucket_index];

  for(struct list_node_t* curr = bucket; curr != NULL; curr = curr->next) {
    struct map_node_t* map_node = curr->value;
    if(strcmp(map_node->key, key) == 0) {
      map->buckets[bucket_index] = remove_from_list(bucket, curr);
      map->count--;
      return;
    }
  }
}

void* get_from_map(struct map_t* map, char* key) {
  if(!has_in_map(map, key)) return NULL;

  unsigned int bucket_index = hash_func(key) % BUCKET_COUNT;

  for(struct list_node_t* curr = map->buckets[bucket_index]; curr != NULL; curr = curr->next) {
    struct map_node_t* map_node = curr->value;
    if(strcmp(map_node->key, key) == 0) return map_node->value;
  }

  return NULL;
}

void print_all_in_map(struct map_t* map) {
  for(int bucket_index = 0; bucket_index < BUCKET_COUNT; bucket_index++) {
    struct list_node_t* bucket = map->buckets[bucket_index];

    if(bucket == NULL) {
      printf("[B=%.2d] empty\n", bucket_index);
      continue;
    }

    struct list_node_t* curr = bucket;
    for(int i = 0; curr != NULL; i++, curr = curr->next) {
      struct map_node_t* map_node = curr->value;
      printf("[B=%.2d] [i=%.2d] K=\"%s\" V=%p\n", bucket_index, i, map_node->key, map_node->value);
    }
  }
}

