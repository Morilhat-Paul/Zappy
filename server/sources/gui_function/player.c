/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** player
*/

#include "gui.h"
#include "player.h"
#include "resources.h"
#include "send_message.h"

void send_teams(server_t *server, player_t *gui, const char **)
{
    for (int i = 0; i < server->options->nb_name; i++)
        add_to_gui_buffer(gui, "tna %s\n", server->options->name[i]);
}

void send_inv(player_t *gui, player_t *player)
{
    char buffer[512];
    char tmp[20];

    sprintf(buffer, "pin %d %d %d", player->id, player->x, player->y);
    for (int i = 0; i < NB_RESOURCE; i++) {
        sprintf(tmp, " %d", player->resources[i].quantity);
        strcat(buffer, tmp);
    }
    strcat(buffer, "\n");
    add_to_gui_buffer(gui, buffer);
}

void send_inv_to_all_gui(server_t *server, player_t *player)
{
    char buffer[512];
    char tmp[20];

    sprintf(buffer, "pin %d %d %d", player->id, player->x, player->y);
    for (int i = 0; i < NB_RESOURCE; i++) {
        sprintf(tmp, " %d", player->resources[i].quantity);
        strcat(buffer, tmp);
    }
    add_to_all_gui(server, "%s\n", buffer);
}

void player_inv(server_t *server, player_t *gui, const char **args)
{
    int id;
    player_t *player;

    if (!args)
        return;
    id = atoi(args[0]);
    SLIST_FOREACH(player, &server->head_players, next) {
        if (PLAYER_IS_AI(player) && player->id == id)
            return send_inv(gui, player);
    }
}

void new_ai_logged(server_t *server, player_t *player)
{
    add_to_all_gui(server, "pnw %d %d %d %d %d %s\n", player->id, player->x,
        player->y, player->direction, player->level, player->team);
    send_inv_to_all_gui(server, player);
    add_to_all_gui(server, "ebo %d\n", player->id);
}
