#include "defs.h"
// 1 if two strings are "connected", zero otherwise
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
