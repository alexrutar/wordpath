#include "defs.h"


// initialize the graph g
struct graph *init_graph(void) {
    // filename #define'd in defs.h (defaults to "four.txt")
    FILE *fp = fopen(GRAPH_FILE, "rb");
    struct graph *g;
    if (fp == NULL) {
        printf("%s does not exist, building...\n", GRAPH_FILE);
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
        printf("%s already exists, reading...\n", GRAPH_FILE);
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


// args: 1 = end word
//       2 = start word
int main (int argc, char *argv[]) {
    struct graph *g = init_graph();
    if(argc != 3) {
        printf("usage:\n./wordpath [start-word] [end-word]\n");
        return 0;
    }
    print_path(g, argv[2], argv[1]);
    /* print_degree(g, 3); */
}

