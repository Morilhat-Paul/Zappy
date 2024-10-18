/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** incantation
*/

#include "command_functions.h"
#include "struct_player.h"
#include "send_message.h"
#include "incantation.h"
#include "send_message.h"

void function_incantation(server_t *server, player_t *player, const char **)
{
    player_t *player_it = NULL;
    const tile_t *tile = &server->map[player->y][player->x];
    const int level = player->level - 1;
    unsigned int player_nb = 0;

    for (int res = 1; res < 6; res++) {
        if (tile->resources[res].quantity < resources_level[level][res]) {
            send_to(player->socket, "ko\n");
            return;
        }
    }
    SLIST_FOREACH(player_it, &server->head_players, next) {
        if ((player_it->x == player->x) && (player_it->y == player->y))
            player_nb++;
    }
    if (player_nb < resources_level[level][0]) {
        send_to(player->socket, "ko\n");
        return;
    }
    player_it = NULL;
    SLIST_FOREACH(player_it, &server->head_players, next) {
        if (!(player_it->x == player->x) && (player_it->y == player->y))
            continue;
        if (player_it->level == player->level) {
            player_it->level++;
            add_to_all_gui(server, "plv %d %d\n", player->id, player->level);
        }
    }
    send_to(player->socket, "Current level: %d", player->level);
}
