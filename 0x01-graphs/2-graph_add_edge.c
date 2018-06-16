#include "graphs.h"

/**
 * graph_add_edge - add an edge between two nodes in a graph
 *
 * @graph: graph to add edge in
 * @src: source vertex content
 * @dest: destination vertex content
 * @type: type of edge, can be undirected or directed
 *
 * Return: 1 for success, 0 for failure. In case of 0, no edge is made
 */
int graph_add_edge(graph_t *graph, const char *src, const char *dest, edge_type_t type)
{
    vertex_t *vertex_1, *vertex_2;
    int e_1_ret = 1, e_2_ret = 1;

    /* Find vertices */
    vertex_1 = find_vertex(graph, src);
    vertex_2 = find_vertex(graph, dest);
    if (vertex_1 == NULL || vertex_2 == NULL)
        return (0);
    
    /* Add edges to vertices */
    e_1_ret = add_edge(vertex_1, vertex_2);
    if (e_1_ret)
        vertex_1->nb_edges++;
    if (type == BIDIRECTIONAL)
    {
        e_2_ret = add_edge(vertex_2, vertex_1);
        if (e_2_ret)
            vertex_2->nb_edges++;
    }        

    return ((!e_1_ret || !e_2_ret) ? 0 : 1);
}

/**
 * find_vertex - find a vertex in a graph, given it's content
 *
 * @graph: graph to search
 * @content: content of vertex
 *
 * Return: pointer to vertex struct
 */
vertex_t *find_vertex(graph_t *graph, const char *content)
{
    vertex_t *vertex;

    vertex = graph->vertices;
    while (vertex != NULL)
    {
        if (!strcmp(content, vertex->content))
            return (vertex);
        vertex = vertex->next;
    }

    return (vertex);
}

/**
 * add_edge - add an edge in a graph on vertex @src pointing to vertex @dest
 *
 * @src: source vertex
 * @dest: destination vertex
 *
 * Return: 1 for success, 0 for failure
 */
int add_edge(vertex_t *src, vertex_t *dest)
{
    edge_t *edge, *next_edge;

    /* Create edge */
    edge = malloc(sizeof(edge_t));
    if (edge == NULL)
        return (0);
    edge->dest = dest;
    edge->next = NULL;

    /* Add edge */
    if (src->edges == NULL)
        src->edges = edge;
    else
    {
        next_edge = src->edges;
        while (next_edge->next != NULL)
            next_edge = next_edge->next;
        next_edge->next = edge;
    }

    return (1);
}
