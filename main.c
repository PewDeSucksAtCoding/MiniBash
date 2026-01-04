#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h" // Our own file

int main(void) {
    char input[1024];

    while (1) {
        printf("mini-bash> "); // Command line itself
        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = 0; // Getting rid of the newline character at the end of the command

        if (strcmp(input, "exit") == 0) break; // Exiting the program on 'exit' command

        printf("You attempted to run a command: %s\n", input);
    }

    return 0;
}