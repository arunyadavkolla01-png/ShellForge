#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"

int main()
{
    char *line;
    char **tokens;

    initialize_signals();

    printf("\n");
    printf("%s Version 7.0\n", SHELL_NAME);
    printf("\n");

    while(1)
    {
        printf("myshell> ");
        line = read_line();
        if(line == NULL) break;

        if(strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        /* Check for pipe */
        char *pipe_pos = strchr(line, '|');
        if(pipe_pos != NULL)
        {
            *pipe_pos = '\0';
            char *left = line;
            char *right = pipe_pos + 1;

            char **cmd1 = parse_line(left);
            char **cmd2 = parse_line(right);

            execute_pipe(cmd1, cmd2);

            free_tokens(cmd1);
            free_tokens(cmd2);
        }
        else
        {
            tokens = parse_line(line);
            if(execute_builtin(tokens) == 0)
            {
                execute(tokens);
            }
            free_tokens(tokens);
        }
        free(line);
    }

    printf("Goodbye!\n");
    return 0;
}
