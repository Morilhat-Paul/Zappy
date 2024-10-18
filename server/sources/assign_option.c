/*
** EPITECH PROJECT, 2024
** server
** File description:
** message
*/

#include "../includes/parsing.h"

void false_value(int j, option_t options[], int value)
{
    if (options[j].condition != NULL && !options[j].condition(value)) {
        helper();
        exit(84);
    }
}

void assign_option(const char **av, parsing_t *option, int i)
{
    int value = 0;
    option_t options[] = {
        {"-p", check_port, set_port, 0, 65535},
        {"-x", check_width_height, set_width, 10, 30},
        {"-y", check_width_height, set_height, 10, 30},
        {"-c", check_clients_nb, set_clients_number, 0, 201},
        {"-f", check_frequence, set_frequence, 1, INT_MAX},
        {"-n", NULL, check_name_wrapper, 0, 0}
    };

    for (size_t j = 0; j < sizeof(options) / sizeof(options[0]); ++j) {
        if (strcmp(av[i], options[j].option) == 0) {
            i += 1;
            value = atoi(av[i]);
            false_value(j, options, value);
            options[j].action(option, value, av, i);
            return;
        }
    }
}
