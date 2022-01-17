#include "defs.h"

// 1 if two strings are adjacent, 0 otherwise
int init_connected(char str1[], char str2[]) {
    int b1 = str1[0] - str2[0];
    int b2 = str1[1] - str2[1];
    int b3 = str1[2] - str2[2];
    int b4 = str1[3] - str2[3];
    if(
            (b1 == 0 && b2 == 0 && b3 == 0 && b4 != 0) ||
            (b1 == 0 && b2 == 0 && b3 != 0 && b4 == 0) ||
            (b1 == 0 && b2 != 0 && b3 == 0 && b4 == 0) ||
            (b1 != 0 && b2 == 0 && b3 == 0 && b4 == 0)) return 1;
    return 0;
}

struct graph *init_graph(void) {
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

