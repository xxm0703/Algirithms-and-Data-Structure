#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char* ltrim(char*);
char* rtrim(char*);
char** split_string(char*);

int parse_int(char*);

void put_node(int node, int value, int starting_node, int * result);

typedef struct {
    int node;
    int distance;
} node_holder;

typedef struct {
    int top;
    int back;
    node_holder *buffer; 
} queue;

node_holder pop(queue *que);
void push (queue * que, node_holder node_hol);
queue init_queue(int elements_count);
int is_empty(queue *que);

int is_visited(int * visited, int visited_length, int node);

/*
 * Complete the 'bfs' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 *  3. 2D_INTEGER_ARRAY edges
 *  4. INTEGER s
 */

/*
 * To return the integer array from the function, you should:
 *     - Store the size of the array to be returned in the result_count variable
 *     - Allocate the array statically or dynamically
 *
 * For example,
 * int* return_integer_array_using_static_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     static int a[5] = {1, 2, 3, 4, 5};
 *
 *     return a;
 * }
 *
 * int* return_integer_array_using_dynamic_allocation(int* result_count) {
 *     *result_count = 5;
 *
 *     int *a = malloc(5 * sizeof(int));
 *
 *     for (int i = 0; i < 5; i++) {
 *         *(a + i) = i + 1;
 *     }
 *
 *     return a;
 * }
 *
 */
int* bfs(int n, int m, int edges_rows, int edges_columns, int** edges, int s, int* result_count) {
    int count = n - 1;
   
    int *result = malloc(sizeof(int) * count);
    for (int i = 0; i < count; i++) {
        result[i] = -1;
    }
    
    int * visited = malloc(sizeof(int) * n);
    int visited_length = 0;
    
    queue que = init_queue(n);
    
    visited[visited_length] = s;
    visited_length++;
    
    node_holder starting_node_hol;
    starting_node_hol.node = s;
    starting_node_hol.distance = 0;
    push(&que, starting_node_hol);
    
    while (!is_empty(&que)) {
        node_holder cur_node_hol = pop(&que);
        int distance = cur_node_hol.distance;
        if (cur_node_hol.node != s) {
            put_node(cur_node_hol.node, distance, s, result);
        }
        for (int i = 0; i < m; i++) {
            int first_edge_node = edges[i][0];
            int second_edge_node = edges[i][1];
            if (cur_node_hol.node == first_edge_node && !is_visited(visited, visited_length, second_edge_node)) {
                visited[visited_length] = second_edge_node;
                visited_length++;
                node_holder child_node;
                child_node.node = second_edge_node;
                child_node.distance = distance + 6;
                push(&que, child_node);
            } 
            if (cur_node_hol.node == second_edge_node && !is_visited(visited, visited_length, first_edge_node)) {
                visited[visited_length] = first_edge_node;
                visited_length++;
                node_holder child_node;
                child_node.node = first_edge_node;
                child_node.distance = distance + 6;
                push(&que, child_node);
            }
        }
    }
    
    *result_count = count;
    return result;
}

void put_node(int node, int value, int starting_node, int * result) {
    if (node < starting_node) {
        result[node-1] = value;
    } else {
        result[node-2] = value;
    }
}

node_holder pop(queue * que) {
    node_holder result = que->buffer[que->top];
    que->top++;
    return result;
}

void push (queue * que, node_holder node_hol) {
    que->buffer[que->back] = node_hol;
    que->back++;    
}

queue init_queue(int elements_count) {
    queue new_queue;
    new_queue.buffer = malloc(sizeof(node_holder) * elements_count);
    new_queue.top = 0;
    new_queue.back = 0;
    
    return new_queue;
}

int is_empty(queue * que) {
    if (que->top == que->back) {
        return 1;
    }
    
    return 0;
}

int is_visited(int *visited, int visited_length, int node) {
    for (int i = 0; i < visited_length; i++) {
        if (visited[i] == node) {
            return 1;
        }
    }
    
    return 0;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char** first_multiple_input = split_string(rtrim(readline()));

        int n = parse_int(*(first_multiple_input + 0));

        int m = parse_int(*(first_multiple_input + 1));

        int** edges = malloc(m * sizeof(int*));

        for (int i = 0; i < m; i++) {
            *(edges + i) = malloc(2 * (sizeof(int)));

            char** edges_item_temp = split_string(rtrim(readline()));

            for (int j = 0; j < 2; j++) {
                int edges_item = parse_int(*(edges_item_temp + j));

                *(*(edges + i) + j) = edges_item;
            }
        }

        int s = parse_int(ltrim(rtrim(readline())));

        int result_count;
        int* result = bfs(n, m, m, 2, edges, s, &result_count);

        for (int i = 0; i < result_count; i++) {
            fprintf(fptr, "%d", *(result + i));

            if (i != result_count - 1) {
                fprintf(fptr, " ");
            }
        }

        fprintf(fptr, "\n");
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}