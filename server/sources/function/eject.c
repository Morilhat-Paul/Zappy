/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** eject
*/

#include "command_functions.h"
#include "struct_player.h"
#include "send_message.h"
#include "player.h"

void function_eject(server_t *server, player_t *player, const char **)
{
    switch (player->direction) {
        case N:
            player->y += 1;
            break;
        case E:
            player->x += 1;
            break;
        case S:
            player->y -= 1;
            break;
        case W:
            player->x -= 1;
            break;
        default:
            break;
    }
    check_limits(server, player);
    send_to(player->socket, "ok\n");
}
