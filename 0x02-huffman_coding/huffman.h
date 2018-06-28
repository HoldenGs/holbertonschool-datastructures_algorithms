
#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "heap/heap.h"
#include <stdio.h>

/**
 * struct symbol_s - Stores a char and its associated frequency
 *
 * @data: The character
 * @freq: The associated frequency
 */
typedef struct symbol_s
{
	char data;
	size_t freq;
} symbol_t;

/**
 * struct char_freq_s - Stores a two vector arrays for symbols and
 * their frequencies, plus the size of each
 *
 * @data_v: vector of characters
 * @freq_v: vector of frequencies
 * @size: size of the vectors
 */
typedef struct char_freq_s
{
	char *data;
	size_t *freq;
	size_t size;
} char_freq_t;

/* Prototypes */
symbol_t *symbol_create(char data, size_t freq);
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);
int huffman_extract_and_insert(heap_t *priority_queue);
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);

/* Huffman Codes Prototypes */
int huffman_codes(char *data, size_t *freq, size_t size);
void print_huffman_tree_r(binary_tree_node_t *root, char *code, size_t depth);
size_t get_depth(binary_tree_node_t *root, size_t depth);
void free_codes(binary_tree_node_t *root);


/* Main Huffman Program Prototypes */
int compress(const char *in_file, const char *out_file);
int decompress(const char *in_file, const char *out_file);
char_freq_t *count_symbols(const char *in_file);

#endif /* _HUFFMAN_H_ */
