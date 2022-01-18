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
            return print_shortest_path(g, argv[2], argv[3]);
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
        if(argc != 3) {
            fprintf(stderr, "usage: wordpath farthest WORD\n");
            return 1;
        } else {
            return print_farthest(g, argv[2]);
        }
    }

    else if(strcmp(argv[1], "diameter") == 0) {
        if(argc != 2) {
            fprintf(stderr, "usage: wordpath diameter\n");
            return 1;
        } else {
            return print_max_dist(g);
        }
    }

    else if(strcmp(argv[1], "isolated") == 0) {
        if(argc != 2) {
            fprintf(stderr, "usage: wordpath isolated\n");
            return 1;
        } else {
            return print_isolated(g);
        }
    }

    else {
        fprintf(stderr, "usage: wordpath [adjacent|search] ...\n");
        fprintf(stderr, "Invalid option %s\n", argv[2]);
        return 1;
    }
}
