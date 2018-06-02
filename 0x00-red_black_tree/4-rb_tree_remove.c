#include "rb_trees.h"

/**
 * rb_tree_remove - remove an RB tree node, rebalance the tree,
 * and return the removed node
 *
 * @root: root of tree
 * @n: data to remove
 *
 * Return: 
 */
rb_tree_t *rb_tree_remove(rb_tree_t *root, int n)
{
	int done;

	done = 0;
	root = rb_tree_remove_r(root, n, &done);
	if (root != NULL)
		root->color = BLACK;

	return (root);
}

/**
 * rb_tree_remove_r - recursive helper function to actually delete the node
 *
 * @root: root of the current subtree
 * @n: data of node to delete
 *
 * Return: root of tree
 */
rb_tree_t *rb_tree_remove_r(rb_tree_t *root, int n, int *done)
{
	int direction;
	rb_tree_t *save;

	if (root == NULL)
		*done = 1;
	else
	{
		if (n == root->n)
		{
			if (root->left == NULL || root->right == NULL)
			{
				if (root->left == NULL)
					save = root->right;
				if (is_red(root))
					*done = 1;
				else if (is_red(save))
				{
					save->color = BLACK;
					*done = 1;
				}
				free(root);
				return (save);
			}
			else
			{
				save = root->left;
				while (save->right != NULL)
					save = save->right;
				root->n = save->n;
				n = save->n;
			}
		}
		
		if (n > root->n)
		{
			direction = 1;
			root->right = rb_tree_remove_r(root->right, n, done);
			if (root->right != NULL)
				root->right->parent = root;
		}
		else
		{
			direction = 0;
			root->left = rb_tree_remove_r(root->left, n, done);
			if (root->left != NULL)
				root->left->parent = root;
		}
		if (!*done)
				root = rb_rebalance(root, direction, done);
	}
	return (root);
}

/**
 * rb_rebalance - rebalance any red or black violations made by deleting
 * a node
 *
 * @root: root of the subtree
 * @direction: which child to choose
 * @done: whether we're finished balancing or not, 1 for finished, 0 for not
 *
 * Return: root of subtree
 */
rb_tree_t *rb_rebalance(rb_tree_t *root, int direction, int *done)
{
    rb_tree_t *p;
    rb_tree_t *s;

    p = root;
    if (direction)
    	s = root->left;
    else
    	s = root->right;
    /* Case reduction, remove red sibling */
    if (is_red(s))
    {
        root = single_rotate(root, direction);
        if (direction)
        	s = p->left;
        else
        	s = p->right;
    }

    if (s != NULL)
    {
        if (!is_red(s->left) && !is_red(s->right))
        {
            if (is_red(p))
            {
                *done = 1;
            }

            p->color = BLACK;
            s->color = RED;
        }
        else
        {
            rb_color_t save_color = p->color;
            int new_root = (root == p);

            if (direction)
            {
	            if (is_red(s->left))
	                p = single_rotate(p, direction);
	            else
	                p = double_rotate(p, direction);
            }
            else
            {
	            if (is_red(s->right))
	                p = single_rotate(p, direction);
	            else
	                p = double_rotate(p, direction);
            }

            p->color = save_color;
            p->left->color = BLACK;
            p->right->color = BLACK;

            if (new_root)
                root = p;
            else
            {
            	if (direction)
            		root->right = p;
            	else
            		root->left = p;
            }

            *done = 1;
        }
    }

    return root;
}


/**
 * single_rotate - rotate a binary tree from a given @root
 *
 * @root: root to rotate
 * @direction: direction to rotate. 1 is right, 0 is left
 *
 * Return: the new root after rotation
 */
rb_tree_t *single_rotate(rb_tree_t *root, int direction)
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
    root->color = RED;
    tmp->color = BLACK;
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
        root->left = single_rotate(root->left, !direction);
    else
        root->right = single_rotate(root->right, !direction);
    return (single_rotate(root, direction));
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



