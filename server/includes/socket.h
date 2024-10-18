/*
** EPITECH PROJECT, 2024
** server
** File description:
** socket
*/

#ifndef SOCKET_H_
    #define SOCKET_H_

    #include <arpa/inet.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <sys/ioctl.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #include "struct_server.h"

    #define SA struct sockaddr

/**
** @brief Create the server socket
** @param server The server struct
**/
void socket_create(server_t *server);

/**
** @brief Bind the server socket
** @param server The server struct
**/
void socket_bind(server_t *server);

/**
** @brief Set the socket options
** @param server The server struct
** @param on The __optval parameter
**/
void socket_set_options(server_t *server, int on);


// void sockets_close(server_t *server);

#endif /* !SOCKET_H_ */
