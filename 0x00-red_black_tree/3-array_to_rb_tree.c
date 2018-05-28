#include "rb_trees.h"

/**
 * array_to_rb_tree - convert an array to an RB-tree
 *
 * @array: array to convert
 * @size: size of array
 *
 * Return: root node of RB-tree
 */
rb_tree_t *array_to_rb_tree(int *array, size_t size)
{
	size_t i;
	rb_tree_t *root;

	root = NULL;
	for (i = 0; i < size; i++)
		rb_tree_insert(&root, array[i]);

	return (root);
}
