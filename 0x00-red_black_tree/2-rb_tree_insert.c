#include "rb_trees.h"

/**
 *
 */
rb_tree_t *rb_tree_insert(rb_tree_t **tree, int n)
{
    rb_tree_t *ret, *root;

    root = *tree;
    ret = NULL;
    if (root == NULL)
    {
        /* Empty tree case */
        root = rb_tree_node(NULL, n, BLACK);
        *tree = root;
        ret = root;

        return (ret);
    }
    else
    {
        rb_tree_t head = { 0 }; /* False tree root */

        rb_tree_t *g, *t;     /* Grandparent & parent */
        rb_tree_t *p, *q;     /* Iterator & parent */
        int dir = 0, last;

        /* Set up helpers */
        t = &head;
        g = p = NULL;
        q = t->right = root;

        /* Search down the tree */
        for (;;)
        {
            if (q == NULL)
            {
                /* Insert new node at the bottom */
                if (dir)
                {
                    p->right = q = rb_tree_node(p, n, RED);
                    ret = p->right;
                }
                else
                {
                    p->left = q = rb_tree_node(p, n, RED);
                    ret = p->left;
                }

                if (q == NULL)
                    return (q);
            }
            else if (is_red(q->left) && is_red(q->right))
            {
                /* Color flip */
                q->color = RED;
                q->left->color = BLACK;
                q->right->color = BLACK;
            }

            /* Fix red violation */
            if (is_red(q) && is_red(p))
            {
                int dir2 = t->right == g;

                if (last)
                {
                    if (q == p->right)
                    {
                        if (dir2)
                            t->right = single_rotate(g, !last);
                        else
                            t->left = single_rotate(g, !last);
                    }
                    else
                    {
                        if (dir2)
                            t->right = double_rotate(g, !last);
                        else
                            t->left = double_rotate(g, !last);
                    }
                }
                else
                {
                    if (q == p->left)
                    {
                        if (dir2)
                            t->right = single_rotate(g, !last);
                        else
                            t->left = single_rotate(g, !last);
                    }
                    else
                    {
                        if (dir2)
                            t->right = double_rotate(g, !last);
                        else
                            t->left = double_rotate(g, !last);
                    }
                }
            }

            /* Stop if found */
            if (q && q->n == n)
                break;

            last = dir;
            dir = q->n < n;

            /* Update helpers */
            if (g != NULL)
                t = g;

            g = p, p = q;
            if (dir)
                q = q->right;
            else
                q = q->left;
        }

        /* Update root */
        *tree = head.right;
    }

    /* Make root black */
    root->color = BLACK;

    return (ret);
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

