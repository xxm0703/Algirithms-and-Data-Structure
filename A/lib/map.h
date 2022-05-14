#pragma once

struct map_t;

struct map_t* init_map();

void add_to_map(struct map_t* map, char* key, short value);

int has_in_map(struct map_t* map, char* key);

void remove_from_map(struct map_t* map, char* key);

void* get_from_map(struct map_t* map, char* key);

void print_all_in_map(struct map_t* map);
