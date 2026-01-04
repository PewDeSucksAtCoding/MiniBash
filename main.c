#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "parser.h" // Our own file
#include "executor.h" // Our own file

int main(void) {
    char cwd[1024]; // This is used for storing the current working directory
    char input[1024];
    char **args;

    while (1) {
        // Using the current working directory to make the user experience better
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s mini-bash> ", cwd);
        } else {
            printf("mini-bash> ");
        }

        if (fgets(input, sizeof(input), stdin) == NULL) break;

        input[strcspn(input, "\n")] = 0; // Getting rid of the newline character at the end of the command

        if (strcmp(input, "exit") == 0) break; // Exiting the program on 'exit' command

        // PARSING THE INPUT: check "parsing.h" and "parsing.c"
        args = parse_input(input);

        // EXECUTING THE COMMAND: check "executor.h" and "executor.c"
        execute_command(args);

        free(args); // Freeing the allocated memory: IMPORTANT!

        printf("You attempted to run a command: %s\n", input);
    }

    return 0;
}