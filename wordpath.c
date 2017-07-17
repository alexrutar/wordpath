#include "defs.h"



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

