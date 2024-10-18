/*
** EPITECH PROJECT, 2024
** server
** File description:
** main
*/

#include "server.h"
#include "parsing.h"
#include "logger.h"

int main(int ac, char const *argv[])
{
    parsing_t options = { 0 };

    parsing(ac, &argv[0], &options);
    server(&options);
    return 0;
}
