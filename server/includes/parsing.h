/*
** EPITECH PROJECT, 2024
** server
** File description:
** parsing
*/

#ifndef PARSING_H_
    #define PARSING_H_

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <limits.h>
    #include "struct_network_infos.h"

/* Parsing structure */
typedef struct parsing_s {
    int port;
    int width;
    int height;
    char **name;
    int clientsNb;
    int frequence;
    int nb_name;
} parsing_t;

typedef struct {
    const char *option;
    int (*condition)(int value);
    void (*action)(parsing_t *option, int value, const char **av, int i);
    int min_value;
    int max_value;
} option_t;

void assign_option(const char **av, parsing_t *option, int i);
void continue_parse_name(const char **av, int *i, parsing_t *option);
void check_name(const char **av, parsing_t *option, int i);
void nb_name(const char **av, parsing_t *option);
void set_port(parsing_t *option, int value, const char **av, int i);
void set_width(parsing_t *option, int value, const char **av, int i);
void set_height(parsing_t *option, int value, const char **av, int i);
void set_clients_number(parsing_t *option, int value, const char **av, int i);
void set_frequence(parsing_t *option, int value, const char **av, int i);
int check_port(int value);
int check_width_height(int value);
int check_clients_nb(int value);
int check_frequence(int value);
void check_name_wrapper(parsing_t *option, int value, const char **av, int i);
void helper(void);

#endif /* !parsing_H_ */
