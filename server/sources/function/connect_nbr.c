/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** connect_nbr
*/

#include "command_functions.h"
#include "struct_player.h"
#include "send_message.h"
#include <string.h>

void function_connectnbr(server_t *server, player_t *player, const char **)
{
    int diff = server->options->clientsNb - server->players_connected;

    send_to(player->socket, "%d\n", diff);
}
