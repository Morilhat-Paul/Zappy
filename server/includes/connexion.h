/*
** EPITECH PROJECT, 2024
** server
** File description:
** connexion
*/

#ifndef CONNEXION_H_
    #define CONNEXION_H_

    #include <signal.h>
    #include "socket.h"
    #include "struct_server.h"

    #define CONNEXION_SUCCESS "WELCOME\n"

/**
 * Waits for incoming connections using select().
 *
 * @param server A pointer to the server structure.
 */
void wait_for_connections(server_t *server);

/**
 * Handles incoming connections.
 *
 * @param server A pointer to the server structure.
 */
void handle_incoming_connections(server_t *server);

#endif /* !CONNEXION_H_ */
