#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/map.h"

int main() {
  //char* data = "TOBEORNOTTOBE";
  // char* data = "TOBEORNOTTOBETOBEORNOTTOBE";
   char* data = "TOBEORNOTTOBETOBEORNOTTOBETOBEORNOTTOBETOBEORNOTTOBETOBEORNOTTOBE";

  // Create the lookup table
  struct map_t* lookup_table = init_map();

  // Note all unique chars
  int unique = 0;
  for(int i = 0; i < strlen(data); i++) {
    char tempstr[2] = {data[i], '\0'};
    if(!has_in_map(lookup_table, tempstr))
      add_to_map(lookup_table, tempstr, ++unique);
  }

  puts("=== Table with single chars ===");
  print_all_in_map(lookup_table);
  puts("");

  // Discover unique repeating patterns
  for(int i = 0; i < strlen(data); i++) {
    // Start with 1 character
    char* substr = malloc(2);
    substr[0] = data[i];
    substr[1] = 0;
    int substr_len = 2;

    // Take next char until we get a pattern that doesn't exist in the table
    while(i < strlen(data) && has_in_map(lookup_table, substr)) {
      substr = realloc(substr, substr_len + 1);
      substr[substr_len - 1] = data[++i];
      substr[substr_len] = 0;
      substr_len++;
    }

    // Note the pattern
    add_to_map(lookup_table, substr, ++unique);
  }

  puts("=== Table with added patterns ===");
  print_all_in_map(lookup_table);
  puts("");

  // Filter out unused records from the table
  int filtered_unique = 0;
  struct map_t* filtered_table = init_map();
  for(int i = 0; i < strlen(data); i++) {
    char* substr = malloc(2);
    substr[0] = data[i];
    substr[1] = 0;
    int substr_len = 2;

    while(i < strlen(data) && has_in_map(lookup_table, substr)) {
      substr = realloc(substr, substr_len + 1);
      substr[substr_len - 1] = data[++i];
      substr[substr_len] = 0;
      substr_len++;
    }

    substr[substr_len - 2] = 0;
    i--;

    if(!has_in_map(filtered_table, substr))
      add_to_map(filtered_table, substr, ++filtered_unique);
  }

  puts("=== Filtered Table ===");
  print_all_in_map(filtered_table);
  puts("");

  // Least number of bits to fit all table entries
  int bit_length = 0;
  for(int tmp = filtered_unique; tmp > 0; bit_length++, tmp>>=1);

  // We can't precalculate the number of bytes after compression because they depend on the patterns
  int compressed_size = 1;
  char* output = malloc(2);
  int byte_index = 0;
  int bit_index = 0;
  // Search for the longest pattern that was noted in the table and encode it
  for(int i = 0; i < strlen(data); i++) {
    char* substr = malloc(2);
    substr[0] = data[i];
    substr[1] = 0;
    int substr_len = 2;

    while(i < strlen(data) && has_in_map(lookup_table, substr)) {
      substr = realloc(substr, substr_len + 1);
      substr[substr_len - 1] = data[++i];
      substr[substr_len] = 0;
      substr_len++;
    }

    substr[substr_len - 2] = 0;
    i--;

    // Get the value that corresponds to the pattern
    char compressed_data = get_from_map(lookup_table, substr);
    printf("compress %s to %d\n", substr, compressed_data);
    // Move the value bit by bit to the output
    for(int j = 0; j < bit_length; j++) {
      char bit = 0;
      bit = compressed_data & 1;
      compressed_data >>= 1;

      output[byte_index] <<= 1;
      output[byte_index] |= bit;

      bit_index++;
      if(bit_index == 8) {
        // Add a new byte and start adding bits to it
        bit_index = 0;
        byte_index++;
        output = realloc(output, ++compressed_size + 1);
        // compressed_size++;
      }
    }
  }

  // Set the very last element to 0 to end the string
  output[compressed_size - 1] = '\0';

  puts("=== Result ===");
  printf("unique = %d | bit length = %d\n", filtered_unique, bit_length);
  printf("original size = %lu bits\n", strlen(data) * 8);
  printf("compressed size = %d bits\n", compressed_size * 8);
  printf("ratio = %f\n", (float)compressed_size / strlen(data));
  printf("original: \"%s\"\n", data);
  printf("compressed: \"%s\"\n", output);

  return 0;
}

