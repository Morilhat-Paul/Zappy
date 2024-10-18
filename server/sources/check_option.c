/*
** EPITECH PROJECT, 2023
** server
** File description:
** check_option.c
*/

#include "../includes/parsing.h"

int check_port(int value)
{
    return value > 0 && value < 65535;
}

int check_width_height(int value)
{
    return value >= 10 && value <= 30;
}

int check_clients_nb(int value)
{
    return value > 0 && value < 201;
}

int check_frequence(int value)
{
    return value > 0;
}

void check_name_wrapper(parsing_t *option, int value, const char **av, int i)
{
    (void)value;
    check_name(av, option, i);
}
