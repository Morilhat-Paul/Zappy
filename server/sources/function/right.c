/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** right
*/

#include "command_functions.h"
#include "struct_player.h"
#include "send_message.h"

void function_right(server_t *server, player_t *player, const char **)
{
    player->direction -= 1;
    if (player->direction < 1)
        player->direction += 4;
    send_to(player->socket, "ok\n");
    add_to_all_gui(server, "ppo %d %d %d %d\n",
        player->id,
        player->x,
        player->y,
        player->direction
    );
}
