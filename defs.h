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
    struct vertex *vertices; // pointer to array of vertices
    int *edges; // pointer to vector of ints (adjacency matrix)
};

int count_lines(char *);
int init_connected(char[], char[]);
void print_path(struct graph *g, char *source, char *target);
void print_degree(struct graph *g, int deg);
struct graph *make_graph(char *);
int degree(struct vertex v1);
void print_adjacent(struct graph *g, struct vertex v);
struct vertex get_vertex(char *str, struct graph *g);
struct path min_path(struct graph *g, struct vertex source);
#endif /* DEFS_H */
