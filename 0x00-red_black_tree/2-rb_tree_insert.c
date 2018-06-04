#include "rb_trees.h"

/**
 * rb_tree_insert - insert a node into an RB tree
 *
 * @tree: RB tree
 * @value: value to insert
 *
 * Return: new node inserted into the tree
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node, *ret;

	node = rb_tree_node(NULL, value, RED);
	ret = rb_tree_insert_r(*tree, node);
	if (ret != NULL)
		*tree = ret;
	else
		node = ret;
	(*tree)->color = BLACK;

	return (node);
}

/**
 * rb_tree_insert_r - recurse into RB tree to find point to insert at. After
 * the insertion, the recursion out of the functions checks on each recursed
 * into above the insertion point to check for a Red Violation. This is
 * the only violation we need to search for because we are always inserting
 * a red node.
 *
 * @root: root of the current subtree
 * @node: node to insert
 *
 * Return: current root node
 */
rb_tree_t *rb_tree_insert_r(rb_tree_t *root, rb_tree_t *node)
{
	rb_tree_t *tmp;
	int direction;

	if (root == NULL)
		root = node;
	else if (node->n != root->n)
	{
		if (node->n > root->n)
		{
			direction = 1;
			tmp = root->right;
			root->right = rb_tree_insert_r(root->right, node);
			if (root->right == NULL)
			{
				root->right = tmp;
				return (NULL);
			}
			root = correct_red_violation(root, direction);
		}
		else
		{
			direction = 0;
			tmp = root->left;
			root->left = rb_tree_insert_r(root->left, node);
			if (root->left == NULL)
			{
				root->left = tmp;
				return (NULL);
			}
			root = correct_red_violation(root, direction);
		}
	}
	else
		return (NULL);
	return (root);
}

/**
 * correct_red_violation - correct any red violation found in the subtree
 *
 * @root: root of current subtree
 * @direction: direction of tree a node was inserted in. 1 is right, 0 is
 * left
 *
 * Return: root of subtree
 */
rb_tree_t *correct_red_violation(rb_tree_t *root, int direction)
{
	if (direction)
	{
		root->right->parent = root;
		if (IS_RED(root->right))
		{
			if (IS_RED(root->left))
			{
				root->color = RED;
				root->left->color = BLACK;
				root->right->color = BLACK;
			}
			else if (root->right && IS_RED(root->right->right))
				root = single_rotate(root, !direction, COLOR_SWAP);
			else if (root->right && IS_RED(root->right->left))
				root = double_rotate(root, !direction);
		}
	}
	else
	{
		root->left->parent = root;
		if (IS_RED(root->left))
		{
			if (IS_RED(root->right))
			{
				root->color = RED;
				root->left->color = BLACK;
				root->right->color = BLACK;
			}
			else if (root->left && IS_RED(root->left->left))
				root = single_rotate(root, !direction, COLOR_SWAP);
			else if (root->left && IS_RED(root->left->right))
				root = double_rotate(root, !direction);
		}
	}
	return (root);
}

/**
 * single_rotate - rotate a binary tree from a given @root
 *
 * @root: root to rotate
 * @direction: direction to rotate. 1 is right, 0 is left
 * @color_swap: if COLOR_SWAP (1) is set, swaps to color of the
 * root and new root
 *
 * Return: the new root after rotation
 */
rb_tree_t *single_rotate(rb_tree_t *root, int direction, int color_swap)
{
	rb_tree_t *tmp;

	if (direction)
	{
		tmp = root->left;
		root->left = tmp->right;
		tmp->right = root;
		tmp->parent = root->parent;
		root->parent = tmp;
	}
	else
	{
		tmp = root->right;
		root->right = tmp->left;
		tmp->left = root;
		tmp->parent = root->parent;
		root->parent = tmp;
	}
	if (color_swap)
	{
		root->color = RED;
		tmp->color = BLACK;
	}
	return (tmp);
}

/**
 * double_rotate - rotate a binary tree from a given @root twice. This is
 * used specifically when there is an inner child of a node that needs to
 * be rotated, and needs to be moved to the outside before the proper
 * rotation can be performed.
 *
 * @root: root to rotate
 * @direction: direction to rotate. 1 is right, 0 is left
 *
 * Return: the new root after rotation
 */
rb_tree_t *double_rotate(rb_tree_t *root, int direction)
{
	if (direction)
		root->left = single_rotate(root->left, !direction, NO_COLOR_SWAP);
	else
		root->right = single_rotate(root->right, !direction, NO_COLOR_SWAP);
	return (single_rotate(root, direction, COLOR_SWAP));
}

/**
 * is_red - check if a node is red
 *
 * @node: node to check
 *
 * Return: 1 for red, 0 for black or another color
 */
int is_red(rb_tree_t *node)
{
	return (node != NULL && node->color == RED);
}
