#include "defs.h"

int print_isolated(struct graph *g) {
    // print the isolated vertices in g
    for(int i = 0; i < g->size; ++i) {
        struct vertex v = g->vertices[i];
        if(v.degree == 0) {
            printf("%s\n", v.name);
        }
    }
    return 0;
}
int print_adjacent(struct graph *g, char *source) {
    // prints all the vertices in g that are adjacent to a vertex v
    struct vertex v = get_vertex(source, g);
    int retcode = 1;
    for(int i = 0; i < g->size; ++i) {
        if(connected(g, g->vertices[i], v)) {
            printf("%s\n", g->vertices[i].name);
            retcode = 0;
        }
    }
    return retcode;
}
int print_shortest_path(struct graph *g, char *source, char *target) {
    // print a shortest path connecting source and target
    struct vertex trg = get_vertex(target, g);
    struct vertex src = get_vertex(source, g);
    struct path p = min_path(g, trg);
    if(p.dists[src.index] == INF_DIST) {
        fprintf(stderr, "There is no path from \"%s\" to \"%s\".\n", source, target);
        return 1;
    }
    int start = src.index;
    while(start != trg.index) {
        printf("%s\n", g->vertices[start].name);
        start = p.prev[start];
    }
    printf("%s\n", target);
    free_path(p);
    return 0;
}
int print_farthest(struct graph *g, char *word) {
    // print the word which has farthest distance from the given word
    struct vertex v = farthest(g, get_vertex(word, g));
    printf("%s\n", v.name);
    return 0;
}
int print_max_dist(struct graph *g) {
    // print out the two vertices (as strings) that are the farthest possible distance apart
    // there's probably a faster way to do this
    int total_max = -1;
    int total_src = -1;
    int total_trg = -1;
    for(int i = 0; i < g->size; ++i) {
        struct vertex src = g->vertices[i];
        struct path p = min_path(g, src);
        int max = -1;
        int idx = -1;
        for(int i = 0; i < g->size; ++i) {
            if(p.dists[i] != INF_DIST && p.dists[i] > max) {
                max = p.dists[i];
                idx = i;
            }
        }
        if(max > total_max) {
            total_max = max;
            total_src = i;
            total_trg = idx;
        }
        printf("Step %d of %d: %d maximum distance, from \"%s\" to \"%s\".\n", i, g->size, total_max, g->vertices[total_src].name, g->vertices[total_trg].name);
        free(p.dists);
        free(p.prev);
    }
    printf("Max distance %d, from \"%s\" to \"%s\".\n", total_max, g->vertices[total_src].name, g->vertices[total_trg].name);
    return 0;
}
