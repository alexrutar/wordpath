#include "defs.h"

// 1 if two strings are adjacent, 0 otherwise
int init_connected(char str1[], char str2[]) {
    if(strlen(str1) != strlen(str2)) {
        return 0;
    } else {
        int n_diffs = 0;
        for(int i = 0; i < strlen(str1); ++i) {
            if(str1[i] != str2[i]) ++n_diffs;
        }
        if(n_diffs == 1) {
            return 1;
        } else {
            return 0;
        }
    }
}

struct graph *init_graph(void) {
    // initialize the graph: if the object file exists, read from it; otherwise, build it
    FILE *fp = fopen(GRAPH_FILE, "rb");
    struct graph *g;
    if (fp == NULL) {
        g = make_graph(SOURCE_FILE);
        FILE *g_file = fopen(GRAPH_FILE, "wb+");
        if(g_file != NULL) {
            fwrite(g, sizeof(struct graph), 1, g_file);
            fwrite(g->vertices, sizeof(struct vertex)*g->size, 1, g_file);
            fwrite(g->edges, sizeof(int)*g->size*g->size, 1, g_file);
            for(int i=0; i<g->size; ++i) {
                fwrite(g->vertices[i].name,5, 1, g_file);
            }
            fclose(g_file);
        }
    } else {
        g = malloc(sizeof(struct graph));
        fread(g, sizeof(struct graph), 1, fp);
        g->vertices = malloc(sizeof(struct vertex)*g->size);
        g->edges = malloc(sizeof(int)*g->size*g->size);
        fread(g->vertices, sizeof(struct vertex)*g->size, 1, fp);
        fread(g->edges, sizeof(int)*g->size*g->size, 1, fp);
        for(int i=0; i<g->size; ++i) {
            g->vertices[i].name = malloc(5);
            fread(g->vertices[i].name,5, 1, fp);
        }
        fclose(fp);
    }
    return g;
}

