/*
** EPITECH PROJECT, 2023
** server
** File description:
** set_option.c
*/

#include "../includes/parsing.h"

void set_port(parsing_t *option, int value, const char **av, int i)
{
    (void)av;
    (void)i;
    option->port = value;
}

void set_width(parsing_t *option, int value, const char **av, int i)
{
    (void)av;
    (void)i;
    option->width = value;
}

void set_height(parsing_t *option, int value, const char **av, int i)
{
    (void)av;
    (void)i;
    option->height = value;
}

void set_clients_number(parsing_t *option, int value, const char **av, int i)
{
    (void)av;
    (void)i;
    option->clientsNb = value;
}

void set_frequence(parsing_t *option, int value, const char **av, int i)
{
    (void)av;
    (void)i;
    option->frequence = value;
}
