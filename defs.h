#ifndef DEFS_H
#define DEFS_H
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include <limits.h>

#define MAX_CHAR 100
#define INF_DIST 10000
#define SOURCE_FILE "four.txt"
#define GRAPH_FILE "graph"

struct path {
    int *dists; // distances from the vertex
    int *prev; // index for the next position in an optimal path
};
struct vertex {
    int degree;
    char *name;
    int index;
};
struct graph {
    int size;
    struct vertex *vertices; // array of vertices
    int *edges; // adjacency matrix
};

int count_lines(char *);
int init_connected(char[], char[]);
int connected(struct graph *g, struct vertex v1, struct vertex v2);
struct vertex farthest(struct graph *g, struct vertex source);

struct graph *make_graph(char *);
struct graph *init_graph(void);
struct vertex get_vertex(char *str, struct graph *g);

struct path min_path(struct graph *g, struct vertex source);
void free_path(struct path p);

int print_max_dist(struct graph *g);
int print_shortest_path(struct graph *g, char *source, char *target);
int print_adjacent(struct graph *g, char *source);
int print_farthest(struct graph *g, char *word);
int print_isolated(struct graph *g);
#endif /* DEFS_H */
