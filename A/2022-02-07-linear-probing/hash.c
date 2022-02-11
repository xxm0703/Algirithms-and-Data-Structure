#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESIZE_FACTOR 2

typedef struct pair{
    char *key;
    int value;
} pair_t;

typedef struct hash_table{
    pair_t **pairs;
    size_t size, capacity;
} hash_table;

size_t hash(char *str){
    return str[0];
}

hash_table *hash_init(size_t size){
    hash_table *table = (hash_table *)malloc(sizeof(hash_table));
    table->pairs = (pair_t **)calloc(size, sizeof(pair_t *));
    table->size = 0;
    table->capacity = size;
    return table;
}

hash_table *hash_add(hash_table *, char * const, int);


void destroy_table(hash_table *table) {
    for (size_t i = 0; i < table->size; ++i) {
        if (table->pairs[i])
            free(table->pairs[i]->key);
        free(table->pairs[i]);
    }
    free(table->pairs);
    free(table);
}

hash_table *resize_table(hash_table *table) {
    hash_table *new_table = hash_init(table->capacity * RESIZE_FACTOR);

    for(size_t i = 0; i < table->size; ++i)
        new_table = hash_add(new_table, table->pairs[i]->key, table->pairs[i]->value);
    destroy_table(table);
    return new_table;
}

hash_table *hash_add(hash_table *table, char * const key, int value) {
    
    if (table->size == table->capacity)
        table = resize_table(table);
    
    pair_t *new_pair = (pair_t *)malloc(sizeof(pair_t));
    new_pair->key = (char *)malloc((strlen(key) + 1) * sizeof(char));
    strcpy(new_pair->key, key);
    new_pair->value = value;
    
    size_t index = hash(key) % table->capacity;
    table->pairs[index] = new_pair;
    ++table->size;
    return table;
}

// bool *hash_contains(hash_table *table, char *key);


int main() {
    hash_table ht;
//    ht.contains("10A");
    destroy_table(&ht);
    return 0;
}
