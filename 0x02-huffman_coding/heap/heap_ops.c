#include "heap.h"

#define RIGHT	1
#define LEFT	0

#define FLOOR(n)		(n - (n % 1))
#define CEILING_POS(X) ((X - (int)(X)) > 0 ? (int)(X + 1) : (int)(X))
#define CEILING_NEG(X) ((X - (int)(X)) < 0 ? (int)(X - 1) : (int)(X))
#define CEIL(X)			(((X) > 0) ? CEILING_POS(X) : CEILING_NEG(X))

/**
 * power - compute @n to the power of @e
 *
 * @n: number
 * @e: exponent
 *
 * Return: n^e
 */
int power(int n, int e)
{
	int new_n;

	if (e == 0)
		return (1);
	new_n = power(n, e / 2);
	if (e % 2 == 0)
		return (new_n * new_n);
	else
		return (n * new_n * new_n);
}

/**
 * logarithm2 - compute the log2 of @n
 *
 * @n: number to log
 *
 * Return: 2nd logarithm of @n
 */
int logarithm2(int n)
{
	return ((n > 1) ? 1 + logarithm2(n / 2) : 0);
}

/**
 * push - push node onto stack
 *
 * @stack: pointer to first stack pointer
 * @direction: direction data
 *
 * Return: node pushed or NULL on failure
 */
stack_t *push(stack_t **stack, int direction)
{
	stack_t *node;

	node = malloc(sizeof(stack_t));
	if (node == NULL)
		return (NULL);
	if (*stack != NULL)
		(*stack)->prev = node;
	node->prev = NULL;
	node->next = *stack;
	node->direction = direction;
	*stack = node;

	return (node);
}

/**
 * pop - pop a node from stack
 *
 * @stack: stack to pop from
 *
 * Return: next direction in stack, or -1 on failure
 */
int pop(stack_t **stack)
{
	stack_t *tmp;
	int dir;

	if (*stack == NULL)
		return (-1);
	dir = (*stack)->direction;
	tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
	if (*stack)
		(*stack)->prev = NULL;

	return (dir);
}
