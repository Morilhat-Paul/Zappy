/*
** EPITECH PROJECT, 2023
** server
** File description:
** parsing.c
*/

#include "parsing.h"

void helper(void)
{
    printf(
    "USAGE: ./zappy_server -p port -x width -y height -n name1 name2 ..."
    " -c clientsNb -f freq --auto-start on|off --display-eggs true|false\n"
    " [-v | --verbose]	port		is the port number\n"
    "      width		is the width of the world\n"
    "      height		is the height of the world\n"
    "      nameX		is the name of the team X\n"
    "      clientsNb	is the number of authorized clients per team\n"
    "      freq		is the reciprocal of time unit for execution of actions\n"
    "      auto-start	does the greeting is send automaticly\n"
    "      display-eggs	eggs are visible and destructible\n");
}

void check_opt(const char *av, const char **options,
    const int required_count, int *comp)
{
    for (int j = 0; j < required_count; j++) {
        if (strcmp(av, options[j]) == 0) {
            (*comp)++;
            break;
        }
    }
}

void no_enought_option(int ac, const char **av)
{
    const char *options[] = {"-p", "-x", "-y", "-n", "-c", "-f"};
    int required_count = sizeof(options) / sizeof(options[0]);
    int comp = 0;

    for (int i = 1; i < ac; i++)
        check_opt(av[i], options, required_count, &comp);
    if (comp != required_count) {
        helper();
        exit(84);
    }
}

void parsing(int ac, const char **av, parsing_t *option)
{
    option->name = calloc(option->nb_name, sizeof(char *));
    nb_name(av, option);
    for (int i = 1; i < ac; i++)
        assign_option(av, option, i);
    no_enought_option(ac, av);
}
