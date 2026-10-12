#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "redirect.h"

/*
 * Scans args[] for <, >, >> tokens.
 * Returns 1 if redirection was applied, 0 otherwise.
 */
int handle_redirection(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        /* Input redirection */
        if (strcmp(args[i], "<") == 0 && args[i + 1] != NULL)
        {
            int fd = open(args[i + 1], O_RDONLY);
            if (fd == -1) { perror("open <"); return -1; }
            dup2(fd, STDIN_FILENO);
            close(fd);
            args[i] = NULL;
            return 1;
        }
        /* Append redirection */
        if (strcmp(args[i], ">>") == 0 && args[i + 1] != NULL)
        {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1) { perror("open >>"); return -1; }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            return 1;
        }
        /* Output redirection */
        if (strcmp(args[i], ">") == 0 && args[i + 1] != NULL)
        {
            int fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1) { perror("open >"); return -1; }
            dup2(fd, STDOUT_FILENO);
            close(fd);
            args[i] = NULL;
            return 1;
        }
    }
    return 0;
}
