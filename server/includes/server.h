/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #include "connexion.h"
    #include "socket.h"
    #include "struct_server.h"
    #include "parsing.h"

    #define MAX_CONNECTION 99

void server(const parsing_t *options);
void parsing(int ac, const char **av, parsing_t *option);

#endif /* !SERVER_H_ */
