#include "heap.h"

#define RIGHT	1
#define LEFT	0

#define FLOOR(n)		(n - (n % 1))
#define CEILING_POS(X) ((X - (int)(X)) > 0 ? (int)(X + 1) : (int)(X))
#define CEILING_NEG(X) ((X - (int)(X)) < 0 ? (int)(X - 1) : (int)(X))
#define CEIL(X)			(((X) > 0) ? CEILING_POS(X) : CEILING_NEG(X))

/**
 * heap_insert - insert a node into the min binary heap, and sift up until
 * it's at the correct position relative to it's parents
 *
 * @heap: pointer to heap
 * @data: data to insert
 *
 * Return: node inserted into heap
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *node;
	int *tmp;

	if (heap == NULL)
		return (NULL);

	/* Insert Node */
	if (heap->root == NULL)
	{
		node = binary_tree_node(NULL, data);
		heap->root = node;
	}
	else
		node = insert(heap, data);
	if (node == NULL)
		return (NULL);
	heap->size++;

	/* Sift Up */
	while (node->parent && heap->data_cmp(node->parent->data, node->data) > 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;
		node = node->parent;
	}

	return (node);
}

/**
 * insert - insert a new node at the bottom of the heap
 *
 * @heap: pointer to heap
 * @data: data pointer to insert
 *
 * Return: node inserted, or NULL on failure
 */
binary_tree_node_t *insert(heap_t *heap, void *data)
{
	int level, max_nodes_in_level, max_nodes_in_tree, pos_in_level;
	binary_tree_node_t *parent, *node;
	stack_t *stack;
	double percent_in_level;

	stack = NULL;
	level = FLOOR(logarithm2(heap->size + 1) / logarithm2(2));
	max_nodes_in_level = power(2, level);
	max_nodes_in_tree = power(2, level + 1) - 1;
	pos_in_level = max_nodes_in_level - (max_nodes_in_tree - (heap->size + 1));
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
	parent = get_parent(heap, &stack);
	node = binary_tree_node(parent, data);
	if (stack->direction == RIGHT)
		parent->right = node;
	else
		parent->left = node;
	free(stack);

	return (node);
}

/**
 * get_parent - get the parent to the node we'll insert
 *
 * @heap: heap to search in
 * @stack: stack of directions to help us find the parent in log(n) time
 *
 * Return: the parent to the node we'll insert
 */
binary_tree_node_t *get_parent(heap_t *heap, stack_t **stack)
{
	binary_tree_node_t *parent;
	int dir;

	parent = heap->root;
	while ((*stack)->next != NULL)
	{
		dir = pop(stack);
		if (dir == RIGHT)
			parent = parent->right;
		else
			parent = parent->left;
	}

	return (parent);
}
