/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** inventory
*/

#include "command_functions.h"
#include "struct_player.h"
#include "send_message.h"
#include <stdio.h>

void function_inventory(server_t *, player_t *player, const char **)
{
    char buffer[95] = {0};
    int offset = 0;

    offset += snprintf(buffer + offset, 95 - offset, "[ ");
    for (int i = 0; i < NB_RESOURCE; i++) {
        offset += snprintf(buffer + offset, 95 - offset, "%s %u",
        resources_density[i].name, player->resources[i].quantity);
        if (i < NB_RESOURCE - 1) {
            offset += snprintf(buffer + offset, 95 - offset, " , ");
        }
    }
    offset += snprintf(buffer + offset, 95 - offset, " ]\n");
    send_to(player->socket, buffer);
}
