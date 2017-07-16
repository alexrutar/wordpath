#include "defs.h"
// initializes the degree of vertex nd in graph g
int init_degree(int nd, struct graph *g) {
    int sum = 0;
    for(int i = 0; i < g->size; ++i) {
        sum = sum + g->edges[g->size*nd + i];
    }
    return sum;
}

// build the graph from the source file, where sz is the number of lines in the source file
struct graph *make_graph(char *source_file) {
    int sz = count_lines(source_file);
    struct graph *g = malloc(sizeof(struct graph));
    if(sz == -1) return g;
    char string[MAX_CHAR];
    FILE *fp;
    fp=fopen(source_file, "r"); // I open the file to read it("r")

    g->size = sz;

    // initialize names for the vertices
    g->vertices = malloc(sizeof(struct vertex) * sz);
    // open the file and read in all the strings to the vector
    for(int i = 0; fgets(string, MAX_CHAR, fp)!=NULL; ++i) {
        int str_sz = strlen(string);
        string[str_sz-1] = '\0';

        // set the name for the ith vertex
        g->vertices[i].name = malloc(sizeof(string)-1);
        strncpy(g->vertices[i].name, string,str_sz-1);
    }


    g->edges = malloc(sizeof(int *)*sz*sz);
    // build an adjacency matrix for the edges
    for(int i = 0; i < sz; ++i) {
        for(int j = 0; j < sz; ++j) {
            if(init_connected(g->vertices[i].name, g->vertices[j].name)) {
                g->edges[i*sz + j] = 1;
            }
            else g->edges[i*sz + j] = 0;
        }
    }
    // calculate the degrees and indices
    for(int i = 0; i < sz; ++i) {
        g->vertices[i].degree = init_degree(i, g);
        g->vertices[i].index = i;
    }
    return g;
}
void free_graph(struct graph *g) {
    for(int i=0; i<g->size; ++i) {
        free(g->vertices[i].name);
    }
    free(g->vertices);
    free(g->edges);
    free(g);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS ON VERTICES

// returns the degree of a vertex v
int degree(struct vertex v1) {
    return v1.degree;
}
// returns 1 if the vertices are connected, 0 otherwise
int connected(struct graph *g, struct vertex v1, struct vertex v2) {
    return g->edges[v1.index * g->size + v2.index];
}
// strcmp returns negative if a < b, positive if a > b, 0 if a = b
// binary search to find the node in the graph g, assumes vertices are sorted alphabetically
// returns the node immediately before if it doesn't exist
struct vertex get_vertex(char *str, struct graph *g) {
    int low = 0;
    int high = g->size-1;
    while(low <= high) {
        int mid = (low + high)/2;
        if(strcmp(g->vertices[mid].name,str) > 0) {
            high = mid-1;
        } else if (strcmp(g->vertices[mid].name,str) < 0) {
            low = mid+1;
        } else {
            return g->vertices[mid];
        }
    }
    return g->vertices[low];
}
// printes all the vertices in g that are adjacent to a vertex v
void print_adjacent(struct graph *g, struct vertex v) {
    printf("degree %d; ", v.degree);
    printf("%s: ", v.name);
    for(int i = 0; i < g->size; ++i) {
        /* if(init_connected(g->vertices[i].name, v.name)) printf("%s ", g->vertices[i].name); */
        if(connected(g, g->vertices[i], v)) printf("%s ", g->vertices[i].name);
    }
    printf("\n");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int q_empty(int *Q, int sz) {
    for(int i = 0; i < sz; ++i) {
        if(Q[i] != -1) return 0;
    }
    return 1;
}
int min_q(struct graph *g, int *Q, int *dists) {
    int min = 10000000;
    int min_idx = -1;
    for(int i = 0; i < g->size; ++i) {
        if(Q[i] != -1 && dists[i] < min) {
            min_idx = i;
            min = dists[i];
        }
    }
    Q[min_idx] = -1;
    return min_idx;
}
struct path shortest_path(struct graph *g, struct vertex source) {
    int *distances = (int *)malloc(g->size * sizeof(int));
    int *prev = (int *)malloc(g->size * sizeof(int));
    int *Q = (int *)malloc(g->size * sizeof(int));
    for(int i = 0; i < g->size; ++i) {
        distances[i] = INF_DIST;
        prev[i] = -1;
        Q[i] = i;
    }
    distances[source.index] = 0;
    while(!q_empty(Q, g->size)) {
        int u = min_q(g, Q, distances);
        /* printf("%d\n", u); */
        int alt;
        for(int v = 0; v < g->size; ++v) {
            if(connected(g, g->vertices[v], g->vertices[u])) {
                alt = distances[u] + 1;
                if(alt < distances[v]) {
                    distances[v] = alt;
                    prev[v] = u;
                }
            }
        }
    }
    free(Q);
    struct path p;
    p.dists = distances;
    p.prev = prev;
    return p;
}
void print_degree(struct graph *g, int deg) {
    for(int i = 0; i < g->size; ++i) {
        if(degree(g->vertices[i]) == deg) print_adjacent(g, g->vertices[i]);
    }
}
void print_path(struct graph *g, char *source, char *target) {
    struct vertex trg = get_vertex(target, g);
    struct vertex src = get_vertex(source, g);
    struct path p = shortest_path(g, src);
    if(p.dists[trg.index] == INF_DIST) {
        printf("Sorry, there is no path from \"%s\" to \"%s\".", source, target);
        return;
    }
    printf("Distance %d:\n", p.dists[trg.index]);
    int start = trg.index;
    while(start != src.index) {
        printf("%s\n", g->vertices[start].name);
        start = p.prev[start];
    }
    printf("%s\n", source);
}

struct vertex max_reachable(struct graph *g, char *source) {
    struct vertex src = get_vertex(source, g);
    struct path p = shortest_path(g, src);
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
        struct path p = shortest_path(g, src);
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
