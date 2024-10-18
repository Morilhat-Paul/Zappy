/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** forward
*/

#include "command_functions.h"
#include "struct_player.h"
#include "struct_server.h"
#include "send_message.h"

void check_limits(server_t *server, player_t *player)
{
    if (player->x < 0)
        player->x = server->options->width - 1;
    if (player->x == server->options->width)
        player->x = 0;
    if (player->y < 0)
        player->y = server->options->height - 1;
    if (player->y == server->options->height)
        player->y = 0;
}

static void forward(server_t *server, player_t *player)
{
    switch (player->direction) {
        case N:
            player->y -= 1;
            break;
        case E:
            player->x += 1;
            break;
        case S:
            player->y += 1;
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

void function_forward(server_t *server, player_t *player, const char **)
{
    forward(server, player);
    add_to_all_gui(server, "ppo %d %d %d %d\n",
        player->id,
        player->x,
        player->y,
        player->direction
    );
}
