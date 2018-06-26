#include "heap.h"

/**
 * heap_delete - delete the heap and all of it's nodes
 *
 * @heap: heap to delete
 * @free_data: function to use on the data stored in each node
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap->root)
		delete_tree_r(heap->root, free_data);
	free(heap);
}

/**
 * delete_tree_r - recursively delete a binary tree from @node
 *
 * @node: node from which to recursively delete
 * @free_data: function to use on node data
 */
void delete_tree_r(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node->right)
		delete_tree_r(node->right, free_data);
	if (node->left)
		delete_tree_r(node->left, free_data);
	if (free_data)
		free_data(node->data);
	free(node);
}
