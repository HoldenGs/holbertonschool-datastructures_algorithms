#include "graphs.h"
#include <string.h>

/**
 * graph_add_vertex - add a vertex with @str data to the @graph
 *
 * @graph: graph to add vertex to
 * @str: data to put in vertex
 *
 * Return: pointer to vertex struct
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *vertex, *next_vertex;

	/* Create vertex */
	vertex = malloc(sizeof(vertex_t));
	if (vertex == NULL)
		return (NULL);
	vertex->content = strdup(str);
	vertex->nb_edges = 0;
	vertex->edges = NULL;
	vertex->next = NULL;
	vertex->index = 0;
	graph->nb_vertices++;

	/* Insert vertex */
	if (graph->vertices == NULL)
		graph->vertices = vertex;
	else
	{
		next_vertex = graph->vertices;
		vertex->index = 1;
		while (next_vertex->next != NULL)
		{
			if (!strcmp(next_vertex->content, str))
				return (NULL);
			next_vertex = next_vertex->next;
			vertex->index++;
		}
		next_vertex->next = vertex;
	}

	return (vertex);
}
