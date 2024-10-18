/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** take
*/

#include "command_functions.h"
#include "struct_player.h"
#include "struct_server.h"
#include "send_message.h"
#include "gui.h"

resource_t parse_resource(const char *resource_name)
{
    for (int i = 0; i < NB_RESOURCE; i++) {
        if (strncmp(resource_name, resources_density[i].name,
            strlen(resources_density[i].name)) == 0) {
            return resources_density[i].ressource;
        }
    }
    return invalid_resource;
}

static void update_item(server_t *server, player_t *player,
    resource_t resource)
{
    add_to_all_gui(server, "pgt %d %d\n", player->id, resource);
    send_inv_to_all_gui(server, player);
    send_tile_to_all(server, player->x, player->y);
}

void function_take(server_t *server, player_t *player, const char **argv)
{
    resource_t resource;
    tile_t *tile = NULL;

    if (argv == NULL || argv[0] == NULL) {
        send_to(player->socket, "ko\n");
        return;
    }
    resource = parse_resource(argv[0]);
    tile = &server->map[player->y][player->x];
    if (resource == invalid_resource) {
        send_to(player->socket, "ko\n");
    } else if (tile->resources[resource].quantity > 0) {
        tile->resources[resource].quantity--;
        player->resources[resource].quantity++;
        update_item(server, player, resource);
        send_to(player->socket, "ok\n");
    } else {
        send_to(player->socket, "ko\n");
    }
}
