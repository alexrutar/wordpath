#include "defs.h"

void print_degree(struct graph *g, int deg) {
    for(int i = 0; i < g->size; ++i) {
        if(degree(g->vertices[i]) == deg) print_adjacent(g, g->vertices[i]);
    }
}
struct vertex max_reachable(struct graph *g, char *source) {
    struct vertex src = get_vertex(source, g);
    struct path p = min_path(g, src);
    int max = -1;
    int idx = -1;
    for(int i = 0; i < g->size; ++i) {
        if(p.dists[i] != INF_DIST && p.dists[i] > max) {
            max = p.dists[i];
            idx = i;
        }
    }
    return g->vertices[idx];
}

// takes a graph g and prints out the two nodes (as strings) that are the farthest possible distance apart
// it's really slow
// there's probably a faster way to do this
void max_dist(struct graph *g) {
    int total_max = -1;
    int total_src = -1;
    int total_trg = -1;
    for(int i = 0; i < g->size; ++i) {
        struct vertex src = g->vertices[i];
        struct path p = min_path(g, src);
        printf("\n");
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
        printf("Step %d of %d: %d maximum distance, from %s to %s.", i, g->size, total_max, g->vertices[total_src].name, g->vertices[total_trg].name);
        free(p.dists);
        free(p.prev);
    }
    printf("\n%d maximum distance, from %s to %s.", total_max, g->vertices[total_src].name, g->vertices[total_trg].name);
    return;
}
// returns the vertex with the largest degree
struct vertex max_degree(struct graph *g) {
    int cur_max = 0;
    int idx = 0;
    int tmp;
    for(int i = 0; i < g->size; ++i) {
        tmp = g->vertices[i].degree;
        if(tmp > cur_max) {
            idx = i;
            cur_max = tmp;
        }
    }
    return g->vertices[idx];
}
