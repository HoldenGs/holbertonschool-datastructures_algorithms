#include "rb_trees.h"

/**
 * rb_tree_node - create an RB tree node
 *
 * @parent: parent of the node
 * @value: value of the node
 * @color: color of the node
 *
 * Return: pointer to the node
 */
rb_tree_t *rb_tree_node(rb_tree_t *parent, int value, rb_color_t color)
{
	rb_tree_t *node;

	node = malloc(sizeof(rb_tree_t));
	if (node == NULL)
		return (NULL);
	node->parent = parent;
	node->n = value;
	node->color = color;
	node->left = NULL;
	node->right = NULL;
	return (node);
}
