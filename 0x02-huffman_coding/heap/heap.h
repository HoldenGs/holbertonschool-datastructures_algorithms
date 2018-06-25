
#ifndef _HEAP_H_
#define _HEAP_H_

#include <stdlib.h>

/**
 * struct binary_tree_node_s - Binary tree node data structure
 *
 * @data: Data stored in a node
 * @left: Pointer to the left child
 * @right: Pointer to the right child
 * @parent: Pointer to the parent node
 */
typedef struct binary_tree_node_s
{
	void *data;
	struct binary_tree_node_s *left;
	struct binary_tree_node_s *right;
	struct binary_tree_node_s *parent;
} binary_tree_node_t;

/**
 * struct heap_s - Heap data structure
 *
 * @size: Size of the heap (number of nodes)
 * @data_cmp: Function to compare two nodes data
 * @root: Pointer to the root node of the heap
 */
typedef struct heap_s
{
	size_t size;
	int (*data_cmp)(void *, void *);
	binary_tree_node_t *root;
} heap_t;

/**
 * struct stack_t - stack style linked list for inserting into heap
 *
 * @prev: previous node
 * @next: next node
 * @direction: direction to traverse heap
 */
typedef struct stack_s
{
	struct stack_s *prev;
	struct stack_s *next;
	int direction;
} stack_t;

/* Prototypes */
heap_t *heap_create(int (*data_cmp)(void *, void *));
binary_tree_node_t *binary_tree_node(binary_tree_node_t *parent, void *data);

/* Insert Prototypes */
binary_tree_node_t *heap_insert(heap_t *heap, void *data);
binary_tree_node_t *insert(heap_t *heap, void *data);
stack_t *push(stack_t **stack, int direction);
int pop(stack_t **stack);
binary_tree_node_t *get_parent(heap_t *heap, stack_t **stack);
int power(int n, int e);
int logarithm2(int n);

/* Extract Prototypes */
void *heap_extract(heap_t *heap);
void *replace(heap_t *heap);
void replace_root(heap_t *heap, stack_t **stack);

#endif /* _HEAP_H_ */
