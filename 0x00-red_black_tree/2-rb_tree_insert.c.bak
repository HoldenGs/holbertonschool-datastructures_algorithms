#include "rb_trees.h"

/**
 * rb_tree_insert - insert a node into an RB tree, keeping the RB tree functional
 *
 * @tree: RB tree
 * @value: value to insert
 *
 * Return: new node inserted into the tree
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int value)
{
	rb_tree_t *node;

	node = rb_tree_node(NULL, value, RED);
	if (*tree == NULL)
		*tree = node;
	else
		insert_node(*tree, node);

	repair_tree(node);

	*tree = node;
	while ((*tree)->parent != NULL)
		*tree = (*tree)->parent;

	return (node);
}

/**
 * repair_tree - repair a broken RB tree after inserting into it
 *
 * @node: node inserted - this is where we start repairing from
 */
void repair_tree(rb_tree_t *node)
{
	if (node->parent == NULL)
		node->color = BLACK;
	else if (node->parent->color == BLACK)
		return;
	else if (sibling(node->parent)->color == RED)
	{
		/* color uncle and parent black, grandparent red */
		node->parent->color = BLACK;
		sibling(node->parent)->color = BLACK;
		node->parent->parent->color = RED;
		repair_tree(node->parent->parent);
	}
	else
	{
		/* if node is on an inner branch, we need to move it out */
		if (node == node->parent->parent->left->right)
		{
			rotate_left(node->parent);
			node = node->left;
		}
		else if (node == node->parent->parent->right->left)
		{
			rotate_right(node->parent);
			node = node->right;
		}
		if (node == node->parent->left)
			rotate_right(node->parent->parent);
		else
			rotate_left(node->parent->parent);
		node->parent->color = BLACK;
		node->parent->parent->color = RED;
	}
}


/**
 * rotate_left - rotate an RB tree node to the left
 *
 * @node: node to rotate
 */
void rotate_left(rb_tree_t *node)
{
	rb_tree_t *left_child;

	left_child = node->right;
	node->right = left_child->left;
	left_child->parent = node->parent;
	node->parent = left_child;
}


/**
 * rotate_right - rotate an RB tree node to the right
 *
 * @node: node to rotate
 */
void rotate_right(rb_tree_t *node)
{
	rb_tree_t *right_child;
	
	right_child = node->left;
	node->left = right_child->right;
	right_child->parent = node->parent;
	node->parent = right_child;
}


/**
 * sibling - get the sibling to the @node
 *
 * @node: node
 *
 * Return: sibling node
 */
rb_tree_t *sibling(rb_tree_t *node)
{
	if (node->parent == NULL)
		return (NULL);
	if (node == node->parent->left)
		return (node->parent->right);
	else
		return (node->parent->left);
	return (NULL);
}


/**
 * insert_node - recurse into a RB tree and insert a node
 *
 * @root: root of the tree
 * @node: node to insert
 */
void insert_node(rb_tree_t *root, rb_tree_t *node)
{
	if (root->n > node->n)
	{
		if (root->left != NULL)
			insert_node(root->left, node);
		else
			root->left = node;
	}
	else
	{
		if (root->right != NULL)
			insert_node(root->right, node);
		else
			root->right = node;
	}
	node->parent = root;
}
