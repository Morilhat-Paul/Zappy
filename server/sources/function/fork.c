/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** fork
*/

#include "command_functions.h"
#include "struct_player.h"
#include "player.h"
#include "send_message.h"

void function_fork(server_t *server, player_t *player, const char **)
{
    egg_t *egg = NULL;

    create_new_egg(server, player);
    egg = SLIST_FIRST(&server->head_eggs);
    if (egg) {
        send_to(player->socket, "ok\n");
        add_to_all_gui(server, "eht %d\n", egg->id);
    } else {
        send_to(player->socket, "ok\n");
    }
}
