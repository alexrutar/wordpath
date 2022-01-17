#include "defs.h"
int is_all_alpha(char *string) {
    if(strlen(string) != 5) return 0;
    for(int i = 0; string[i] != '\0'; ++i) {
        if(!((string[i]-'a' >= 0 && string[i] - 'a' < 26) || string[i] == '\n')) return 0;
    }
    return 1;
}
void alpha_filter (char *filename) {
    char string[MAX_CHAR];
    FILE *fp;
    fp=fopen(filename, "r");
    while(fgets(string, MAX_CHAR, fp)!=NULL) {
        // acquire lines of the txt file till we reach the end of it.
        // remember that by doing in this way , in each loop, you save the new line in the same string
        if(is_all_alpha(string)) printf("%s", string); // print the string
    }
    fclose(fp);
}
int count_lines(char *filename) {
    FILE *fp;
    int count = 0;  // Line counter (result)

    // Open the file
    fp = fopen(filename, "r");

    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s.", filename);
        return -1;
    }

    // Extract characters from file and store in character c
    for (int c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    // Close the file
    fclose(fp);
    return count;
}
