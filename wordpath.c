#include "defs.h"

int main (int argc, char *argv[]) {
    struct graph *g = init_graph();
    if(argc < 1) {
        fprintf(stderr, "usage: wordpath [adjacent|search] ...\n");
        return 1;
    }

    if(strcmp(argv[1], "search") == 0) {
        if(argc != 4) {
            fprintf(stderr, "usage: wordpath search START END\n");
            return 1;
        }
        else {
            return print_path(g, argv[3], argv[2]);
        }
    }

    else if(strcmp(argv[1], "adjacent") == 0) {
        if(argc != 3) {
            fprintf(stderr, "usage: wordpath adjacent WORD\n");
            return 1;
        } else {
            return print_adjacent(g, argv[2]);
        }
    }

    else if(strcmp(argv[1], "farthest") == 0) {
        if(argc != 2) {
            fprintf(stderr, "usage: wordpath farthest\n");
            return 1;
        } else {
            return max_dist(g);
        }
    }

    else {
        fprintf(stderr, "usage: wordpath [adjacent|search] ...\n");
        fprintf(stderr, "Invalid option %s\n", argv[2]);
        return 1;
    }
}

