#include "huffman.h"

/**
 * freq_cmp - compare the frequency value stored in each data pointer
 *
 * @p1: pointer 1
 * @p2: pointer 2
 *
 * Return: the difference between the first and second frequency
 */
int freq_cmp(void *p1, void *p2)
{
	binary_tree_node_t *n1, *n2;
	symbol_t *s1, *s2;

	n1 = (binary_tree_node_t *)p1;
	n2 = (binary_tree_node_t *)p2;
	s1 = (symbol_t *)n1->data;
	s2 = (symbol_t *)n2->data;

	return (s1->freq - s2->freq);
}

/**
 * huffman_priority_queue - create a priority queue out of arrays of
 * character data and their respective frequencies
 *
 * @data: array of character data
 * @freq: array of frequencies for each character
 * @size: size of the data and freq arrays
 *
 * Return: Min heapified version of the respective arrays
 */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size)
{
	heap_t *heap;
	symbol_t *symbol;
	binary_tree_node_t *node;
	size_t i;

	heap = heap_create(freq_cmp);
	for (i = 0; i < size; i++)
	{
		symbol = symbol_create(data[i], freq[i]);
		node = binary_tree_node(NULL, symbol);
		node = heap_insert(heap, node);
	}

	return (heap);
}
