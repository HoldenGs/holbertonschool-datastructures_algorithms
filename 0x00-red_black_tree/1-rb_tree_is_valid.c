#include "rb_trees.h"

/**
 * rb_tree_is_valid - check if a red-black tree is valid
 *
 * @tree: tree to check
 *
 * Return: 1 if valid tree, 0 if invalid tree
 */
int rb_tree_is_valid(const rb_tree_t *tree)
{
	int left_blength, right_blength, blength;

	if (tree == NULL)
		return (0);
	left_blength = right_blength = blength = 0;
	if (tree->left != NULL)
		left_blength = rb_tree_is_valid(tree->left);
	else
		left_blength = 1;
	if (tree->right != NULL)
		right_blength = rb_tree_is_valid(tree->right);
	else
		right_blength = 1;
	/* Check that black count is equal on both sides */
	if (right_blength == left_blength)
	{
		blength = right_blength;
		if (tree->color == BLACK)
			blength++;
	}
	else
		blength = 0;
	/* Check if root node is black */
	if (tree->parent == NULL && tree->color != BLACK)
		blength = 0;
	/* Check that the color is either red or black */
	if (tree->color != BLACK && tree->color != RED)
		blength = 0;
	/* Check that there are no adjacent reds */
	if (tree->parent && tree->color == RED && tree->parent->color == RED)
		blength = 0;
	/* Convert blength to 1 if tree is valid */
	if (tree->parent == NULL && blength != 0)
		return (1);
	return (blength);
}
