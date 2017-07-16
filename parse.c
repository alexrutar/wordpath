#include "defs.h"


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


// args: 1 = end word
//       2 = start word
int main (int argc, char *argv[]) {
    // filename #define'd in defs.h (defaults to "four.txt")
    FILE *fp = fopen(GRAPH_FILE, "rb");
    struct graph *fg;
    if (fp == NULL) {
        printf("%s does not exist, building...\n", GRAPH_FILE);
        fg = make_graph(SOURCE_FILE);
        FILE *g_file = fopen(GRAPH_FILE, "wb+");
        if(g_file != NULL) {
            fwrite(fg, sizeof(struct graph), 1, g_file);
            fwrite(fg->vertices, sizeof(struct vertex)*fg->size, 1, g_file);
            fwrite(fg->edges, sizeof(int)*fg->size*fg->size, 1, g_file);
            for(int i=0; i<fg->size; ++i) {
                fwrite(fg->vertices[i].name,5, 1, g_file);
            }
            fclose(g_file);
        }
    } else {
        fg = malloc(sizeof(struct graph));
        printf("%s already exists, reading...\n", GRAPH_FILE);
        fread(fg, sizeof(struct graph), 1, fp);
        fg->vertices = malloc(sizeof(struct vertex)*fg->size);
        fg->edges = malloc(sizeof(int)*fg->size*fg->size);
        fread(fg->vertices, sizeof(struct vertex)*fg->size, 1, fp);
        fread(fg->edges, sizeof(int)*fg->size*fg->size, 1, fp);
        for(int i=0; i<fg->size; ++i) {
            fg->vertices[i].name = malloc(5);
            fread(fg->vertices[i].name,5, 1, fp);
        }
        fclose(fp);
    }
    if(argc != 3) {
        printf("usage:\n./wordpath [start-word] [end-word]\n");
        return 0;
    }
    print_path(fg, argv[2], argv[1]);
    /* print_degree(fg, 3); */
}

