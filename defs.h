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
    int *dists;
    int *prev;
    char *source;
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
int print_path(struct graph *g, char *source, char *target);
struct graph *make_graph(char *);
int print_adjacent(struct graph *g, char *source);
struct vertex get_vertex(char *str, struct graph *g);
struct path min_path(struct graph *g, struct vertex source);
struct graph *init_graph(void);
int max_dist(struct graph *g);
#endif /* DEFS_H */
