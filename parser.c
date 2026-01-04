#include <string.h>
#include <stdlib.h>
#include "parser.h"

char** parse_input(char* input) {
    int bufsize = 64;
    int position = 0;

    // Allocating memory for 64 pointers of strings aka the arguments of the command line command
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        exit(EXIT_FAILURE); // Exiting if the allocation fails
    }

    // Slicing the passed command input with strtok
    token = strtok(input, " \t\r\n\a");
    while (token != NULL) {
        tokens[position] = token;
        position++;

        token = strtok(NULL, " \t\r\n\a");
    }

    tokens[position] = NULL;
    return tokens;
}