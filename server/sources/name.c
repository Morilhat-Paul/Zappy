/*
** EPITECH PROJECT, 2023
** server
** File description:
** name.c
*/

#include "parsing.h"

void check_name(const char **av, parsing_t *option, int i)
{
    int actual_name = 0;

    for (int comp = i; av[comp] != NULL; comp++) {
        if (av[comp][0] == '-') {
            break;
        }
        option->name[actual_name] = calloc(strlen(av[comp]), sizeof(char));
        strcpy(option->name[actual_name], av[comp]);
        actual_name++;
    }
}

void continue_parse_name(const char **av, int *i, parsing_t *option)
{
    while (av[*i] != NULL) {
        if (av[*i][0] == '-')
            break;
        (*i)++;
        option->nb_name++;
    }
}

void nb_name(const char **av, parsing_t *option)
{
    for (int i = 0; av[i] != NULL; i++) {
        if (strcmp(av[i], "-n") == 0) {
            i += 1;
            continue_parse_name(av, &i, option);
        }
    }
}
