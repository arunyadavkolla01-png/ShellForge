#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"

int main()
{
    char *line;
    char **tokens;

    printf("\n");
    printf("%s Version 3.0\n", SHELL_NAME);
    printf("\n");

    while(1)
    {
        printf("myshell> ");
        line = read_line();

        if(strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        tokens = parse_line(line);

        printf("Parsed Tokens\n");
        for(int i = 0; tokens[i] != NULL; i++)
            printf("argv[%d] = %s\n", i, tokens[i]);

        free_tokens(tokens);
        free(line);
    }

    printf("Goodbye!\n");
    return 0;
}
