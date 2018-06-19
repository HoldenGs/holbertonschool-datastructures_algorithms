#include "heap.h"

/**
 * heap_create - create an empty heap structure
 *
 * @data_cmp: comparison function for comparing two nodes
 *
 * Return: pointer to heap
 */
heap_t *heap_create(int (*data_cmp)(void *, void *))
{
	heap_t *heap;

	heap = malloc(sizeof(heap_t));
	if (heap == NULL)
		return (NULL);
	heap->size = 0;
	heap->root = NULL;
	heap->data_cmp = data_cmp;
	return (heap);
}
