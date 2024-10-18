/*
** EPITECH PROJECT, 2024
** server
** File description:
** message
*/

#ifndef MESSAGE_H_
    #define MESSAGE_H_

    #include "struct_server.h"

    #define MAX_MSG_SIZE 256

    #define MAX_INPUT_SIZE 256

/**
 * Reads a input from a the stdin of the server.
 *
 * @param server A pointer to the server structure.
 * @return A pointer to the received input.
 */
char *get_server_input(server_t *server);

/**
 * Reads a message from a client socket.
 *
 * @param server A pointer to the server structure.
 * @param socket The client socket descriptor.
 * @return A pointer to the received message.
 */
char *get_message(server_t *server, player_t *player);

void message_to_ai_cmd(player_t *player, const char *msg);

#endif /* !MESSAGE_H_ */
