/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** send_message
*/

#ifndef SEND_MESSAGE_H_
    #define SEND_MESSAGE_H_

    #include <stdarg.h>
    #include "struct_server.h"
    #include "struct_player.h"

void send_message(const int socket, const char *msg);
void send_to(const int socket, const char *format, ...);
void add_to_gui_buffer(player_t *gui, const char *format, ...);
void add_to_all_gui(const server_t *server, const char *format, ...);
#endif /* !SEND_MESSAGE_H_ */
