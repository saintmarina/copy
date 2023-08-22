// Created by Anna Maniuk on 8/21/23
// Programing problems 2.24 from Operating System Concepts 10th edition
// POSIX compliant

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX_LEN 256

char * get_valid_target_file_name(const char* file_name)
{
    int fd = open(file_name, O_RDONLY);
    char new_name[MAX_LEN];
    strcpy(new_name, file_name);

    while (fd != -1) {
        close(fd);
        printf("File already exists. Provide anoter name: ");
        if (scanf("%255s", new_name) != 1) {
            perror("Error reading input.\n");
            exit(EXIT_FAILURE);
        }
        fd = open(new_name, O_RDONLY);
    }

    char *result = malloc(strlen(new_name) + 1);
    if (result != NULL) {
        strcpy(result, new_name);
    } else {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    return result;
}

void copy_file(const char *source, const char *target)
{
    // Open & validate source and target files
    int source_fd, target_fd;

    source_fd = open(source, O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    char *file_name = get_valid_target_file_name(target);
    target_fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC);
    if (target_fd == -1) {
        perror("Error opening target file");
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read;
    while((bytes_read = read(source_fd, buffer, sizeof(buffer)))> 0) {
        ssize_t bytes_writtern = write(target_fd, buffer, bytes_read);
        if (bytes_writtern != bytes_read) {
            perror("Error writing to target file");
            close(source_fd);
            close(target_fd);
            free(file_name);
            exit(EXIT_FAILURE);
        }
    }

    close(source_fd);
    close(target_fd);
    free(file_name);
}

int main(int argc, const char * argv[]) {
    char source_file[MAX_LEN];
    char target_file[MAX_LEN];

    // Request source and target files from the user
    printf("Source: ");
    if (scanf("%255s", source_file) != 1) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    printf("Copy name: ");
    if (scanf("%255s", target_file) != 1) {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    };

    // Copy file contents
    copy_file(source_file, target_file);
    
    printf("Successfully copied contents of %s\n", source_file);
    return 0;
}
