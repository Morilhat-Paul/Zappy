/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** set
*/

#include "command_functions.h"
#include "struct_player.h"
#include "struct_server.h"
#include "send_message.h"
#include "gui.h"

static void update_item(server_t *server, player_t *player,
    resource_t resource)
{
    add_to_all_gui(server, "pdr %d %d\n", player->id, resource);
    send_inv_to_all_gui(server, player);
    send_tile_to_all(server, player->x, player->y);
}

void function_set(server_t *server, player_t *player, const char **argv)
{
    resource_t resource;

    if (argv == NULL || argv[0] == NULL) {
        send_to(player->socket, "ko\n");
        return;
    }
    resource = parse_resource(argv[0]);
    if (resource == invalid_resource) {
        send_to(player->socket, "ko\n");
    } else if (player->resources[resource].quantity > 0) {
        player->resources[resource].quantity--;
        server->map[player->y][player->x].resources[resource].quantity++;
        send_to(player->socket, "ok\n");
        update_item(server, player, resource);
    } else {
        send_to(player->socket, "ko\n");
    }
}
