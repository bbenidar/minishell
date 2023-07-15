
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    size_t size = 4096;
    char *buffer = malloc(sizeof(char) * size); // Allocate memory for the directory path

    if (buffer == NULL) {
        perror("malloc");
        return 1;
    }

    if (getcwd(buffer, size) != NULL) {
        printf("Current working directory: %s\n", buffer);
    } else {
        perror("getcwd");
        free(buffer); // Free the allocated memory
        return 1;
    }

    free(buffer); // Free the allocated memory
    return 0;
}