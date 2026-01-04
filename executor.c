#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"

int execute_command(char **args) {
    if (args[0] == NULL) {
        return 1; // Program won't accept empty commands
    }

    // MAKING THE PROGRAM WORK FOR "cd" COMMAND AS WELL (Because fork() won't work with 'cd' as it's a build-in shell command)
    // *NOTE*: only "cd [args]" works for this program as in line 15 we check whether the given argument is NULL or not
    if (strcmp(args[0], "cd") == 0) {
        if (args[1] == NULL) {
            fprintf(stderr, "mini-bash: no argument was given for the command 'cd'");
        } else {
            if (chdir(args[1]) != 0) { // Using C's chdir function for handling directory changes, it "speaks" directly to system kernel
                perror("mini-bash");
            }
        }
        return 1; // Returning to main.c's while loop without executing the rest of the program
    }

    // -----------------------------------------------------------------------------------------

    // Creating a direct copy of our mini-bash program to the RAM as a child process
    // The parent gets the child processes process-ID as a return value, which is creater than 0
    pid_t pid = fork();

    if (pid == 0) { // The child process gets an expected return value of 0
        // --- CHILD PROCESS ---
        // Wiping the child processes memory out of "mini-bash" and replacing it with the command itself
        // EXAMPLE: with a command "ls" the memory is replaced with "/bin/ls" that contains the command executable
        if (execvp(args[0], args) == -1) {
            perror("mini-bash"); // If the command isn't found, we print an error
        }
        return 0;
    } else if (pid < 0) {
        perror("mini-bash"); // Error in forking
    } else {
        // ---PARENT PROCESS---
        wait(NULL); // Main process waits here for the child process to finish
    }

    return 1;
}