#include "heap.h"

#define RIGHT	1
#define LEFT	0

#define FLOOR(n)		(n - (n % 1))
#define CEILING_POS(X) ((X - (int)(X)) > 0 ? (int)(X + 1) : (int)(X))
#define CEILING_NEG(X) ((X - (int)(X)) < 0 ? (int)(X - 1) : (int)(X))
#define CEIL(X)			(((X) > 0) ? CEILING_POS(X) : CEILING_NEG(X))

/**
 * heap_extract - extract the root value of a binary value and rebuild
 * the heap
 *
 * @heap: heap data structure
 *
 * Return: pointer to the data of the root node
 */
void *heap_extract(heap_t *heap)
{
	int left_diff = -1, right_diff = -1;
	void *data, *tmp;
	binary_tree_node_t *node;

	data = replace(heap);
	if (data == NULL)
		return (NULL);
	heap->size--;
	node = heap->root;
	if (node && node->left)
		left_diff = heap->data_cmp(node->data, node->left->data);
	if (node && node->right)
		right_diff = heap->data_cmp(node->data, node->right->data);
	while (node && ((node->left && left_diff >= 0) ||
					(node->right && right_diff >= 0)))
	{
		if (left_diff > right_diff)
		{
			tmp = node->left->data;
			node->left->data = node->data;
			node->data = tmp;
			node = node->left;
		}
		else
		{
			tmp = node->right->data;
			node->right->data = node->data;
			node->data = tmp;
			node = node->right;
		}
		/* Weird ternary operators save enough space to appease Betty */
		(node && node->left) ? (
			left_diff = heap->data_cmp(node->data, node->left->data))
		: (left_diff = -1);
		(node && node->right) ? (
			right_diff = heap->data_cmp(node->data, node->right->data))
		: (right_diff = -1);
	}
	return (data);
}

/**
 * replace - replace the root node of the heap with the last node in the heap
 *
 * @heap: heap data structure
 *
 * Return: pointer to the data of the original root
 */
void *replace(heap_t *heap)
{
	int level, max_nodes_in_level, max_nodes_in_tree, pos_in_level;
	double percent_in_level;
	stack_t *stack;
	void *data;

	if (heap == NULL || heap->root == NULL)
		return (NULL);
	data = heap->root->data;
	stack = NULL;
	level = FLOOR(logarithm2(heap->size) / logarithm2(2));
	max_nodes_in_level = power(2, level);
	max_nodes_in_tree = power(2, level + 1) - 1;
	pos_in_level = max_nodes_in_level - (max_nodes_in_tree - (heap->size));
	while (level > 0)
	{
		if (pos_in_level % 2)
		{
			if (push(&stack, LEFT) == NULL)
				return (NULL);
		}
		else
		{
			if (push(&stack, RIGHT) == NULL)
				return (NULL);
		}
		percent_in_level = (float)pos_in_level / (float)max_nodes_in_level;
		max_nodes_in_level /= 2;
		pos_in_level = CEIL(percent_in_level * max_nodes_in_level);
		level--;
	}
	replace_root(heap, &stack);

	return (data);
}

/**
 * replace_root - get the last node and replace the root node with its data
 *
 * @heap: heap to search in
 * @stack: stack of directions to help us find the parent in log(n) time
 *
 * Return: the parent to the node we'll insert
 */
void replace_root(heap_t *heap, stack_t **stack)
{
	binary_tree_node_t *node;
	int dir;

	node = heap->root;
	while (*stack != NULL)
	{
		dir = pop(stack);
		if (dir == RIGHT)
			node = node->right;
		else
			node = node->left;
	}
	if (node->parent)
	{
		if (node->parent->left == node)
			node->parent->left = NULL;
		else
			node->parent->right = NULL;
		heap->root->data = node->data;
	}
	else
	{
		heap->root = NULL;
	}
	free(node);
}
