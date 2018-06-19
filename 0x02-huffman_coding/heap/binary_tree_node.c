#include "heap.h"

/**
 * binary_tree_node - creates a binary tree node to insert under @parent
 *
 * @parent: parent node to insert under
 * @data: data to put into node
 *
 * Return: pointer to node created
 */
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data)
{
	binary_tree_node_t *node;

	node = malloc(sizeof(binary_tree_node_t));
	if (node == NULL)
		return (NULL);
	node->parent = parent;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
