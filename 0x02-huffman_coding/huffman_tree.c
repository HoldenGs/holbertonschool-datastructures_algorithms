#include "huffman.h"

/**
 * huffman_tree - build a huffman tree from a priority queue of characters and
 * their frequencies
 *
 * @data: character array
 * @freq: frequency array
 * @size: size of the arrays
 *
 * Return: root node of the huffman tree
 */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	heap_t *heap;
	int ret;

	heap = huffman_priority_queue(data, freq, size);
	while (heap->root->right || heap->root->left)
	{
		ret = huffman_extract_and_insert(heap);
		if (!ret)
			return (NULL);
	}
	root = (binary_tree_node_t *)heap->root->data;
	free(heap->root);
	free(heap);
	return (root);
}
