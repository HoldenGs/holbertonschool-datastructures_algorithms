
#ifndef _GRAPHS_H_
#define _GRAPHS_H_

#include <stdlib.h>
#include <string.h>

/**
 * enum edge_type_e - Enumerates the different types of
 * connection between two vertices
 *
 * @UNIDIRECTIONAL: The connection is made only in one way
 * @BIDIRECTIONAL: The connection is made in two ways
 */
typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;

/**
 * enum visited_type_e - Enumerates the different types of
 * colors determining whether a vertex was visited or not
 *
 * @WHITE: An unvisited vertex
 * @GREY: A visited vertex with unvisited edges
 * @BLACK: A visited vertex with all edges visited
 */
typedef enum visited_type_e
{
	WHITE = 0,
	BLACK
} visited_type_t;

/* Define the structure temporarily for usage in the edge_t */
typedef struct vertex_s vertex_t;

/**
 * struct edge_s - Node in the linked list of edges for a given vertex
 * A single vertex can have many edges
 *
 * @dest: Pointer to the connected vertex
 * @next: Pointer to the next edge
 */
typedef struct edge_s
{
	vertex_t    *dest;
	struct edge_s   *next;
} edge_t;


/**
 * struct vertex_s - Node in the linked list of vertices in the adjency list
 *
 * @index: Index of the vertex in the adjency list.
 * @content: Custom data stored in the vertex (here, a string)
 * @nb_edges: Number of conenctions with other vertices in the graph
 * @edges: Pointer to the head node of the linked list of edges
 * @next: Pointer to the next vertex in the adgency linked list
 *   This pointer points to another vertex in the graph, but it
 *   doesn't stand for an edge between the two vertices
 */
struct vertex_s
{
	size_t      index;
	char        *content;
	size_t      nb_edges;
	edge_t      *edges;
	struct vertex_s *next;
};

/**
 * struct graph_s - Representation of a graph
 * We use an adjency linked list to represent our graph
 *
 * @nb_vertices: Number of vertices in our graph
 * @vertices: Pointer to the head node of our adjency linked list
 */
typedef struct graph_s
{
	size_t      nb_vertices;
	vertex_t    *vertices;
} graph_t;

/**
 * struct vlist_s - linked list for queue struct
 *
 * @next: next linked list node
 * @prev: previous linked list node
 * @vertex: vertex stored in node
 * @depth: current depth of node in traversal
 */
typedef struct vlist_s
{
	struct vlist_s *next;
	struct vlist_s *prev;
	vertex_t *vertex;
	size_t depth;
} vlist_t;

/**
 * struct queue_s - queue struct for vertexes
 *
 * @head: head of queue to push onto
 * @tail: tail of queue to pop from
 */
typedef struct queue_s
{
	vlist_t *head;
	vlist_t *tail;
} queue_t;

/* Prototypes */
graph_t *graph_create(void);
vertex_t *graph_add_vertex(graph_t *graph, const char *str);
void graph_delete(graph_t *graph);

/* Add edge prototypes */
int graph_add_edge(graph_t *graph, const char *src, const char *dest,
	edge_type_t type);
vertex_t *find_vertex(graph_t *graph, const char *content);
int add_edge(vertex_t *src, vertex_t *dest);
int add_two_edges(vertex_t *src, vertex_t *dest);

/* Depth-first-traversal prototypes */
size_t depth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth));
size_t depth_first_traverse_r(vertex_t *vertex,
	void (*action)(const vertex_t *v, size_t depth),
	visited_type_t visited[], size_t depth);

/* Breadth-first-traversal prototypes */
size_t breadth_first_traverse(const graph_t *graph,
	void (*action)(const vertex_t *v, size_t depth));
vlist_t *push(queue_t *queue, vertex_t *vertex, size_t depth);
vlist_t *pop(queue_t *queue);


#endif /* _GRAPHS_H_ */
