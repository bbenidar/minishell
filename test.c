#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ARGC 3

int main(void) {
    char *commands[][MAX_ARGC + 1] = {
        {"ls", NULL},
        {"wc", "-l", NULL},
        {"sort", NULL},
        {"uniq", NULL}
    };

    size_t i, n;
    int prev_pipe, pfds[2];

    n = sizeof(commands) / sizeof(*commands);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++) {
        pipe(pfds);

        if (fork() == 0) {
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Close read end of current pipe (not needed in the child)
            close(pfds[0]);

            // Start command
            execve(commands[i][0], commands[i], NULL);

            perror("execve failed");
            exit(1);
        }

        // Close write end of current pipe (not needed in the parent)
        close(pfds[1]);

        // Save read end of current pipe to use in the next iteration
        prev_pipe = pfds[0];
    }

    // Get stdin from last pipe
    if (prev_pipe != STDIN_FILENO) {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }

    // Start last command
    execve(commands[i][0], commands[i], NULL);

    perror("execve failed");
    exit(1);
}