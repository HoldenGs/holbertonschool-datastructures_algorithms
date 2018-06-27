#include "huffman.h"

/**
 * huffman_extract_and_insert - extract two nodes from the queue and insert
 * a single node that contains the sum of both frequencies of the two
 * extracted nodes
 *
 * @priority_queue: min heap of all the character data and frequencies
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	void *p1, *p2;
	binary_tree_node_t *node, *n1, *n2;
	symbol_t *symbol, *s1, *s2;

	p1 = heap_extract(priority_queue);
	p2 = heap_extract(priority_queue);
	if (p1 == NULL || p2 == NULL)
		return (0);
	n1 = (binary_tree_node_t *)p1;
	n2 = (binary_tree_node_t *)p2;
	s1 = (symbol_t *)n1->data;
	s2 = (symbol_t *)n2->data;
	symbol = symbol_create(-1, s1->freq + s2->freq);
	if (symbol == NULL)
		return (0);
	node = binary_tree_node(NULL, symbol);
	if (node == NULL)
		return (0);
	node->left = n1;
	node->right = n2;
	n1->parent = node;
	n2->parent = node;
	if (heap_insert(priority_queue, node) == NULL)
		return (0);
	return (1);
}
