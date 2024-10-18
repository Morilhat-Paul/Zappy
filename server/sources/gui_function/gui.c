/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** gui
*/

#include "gui.h"
#include "player.h"
#include "resources.h"
#include "send_message.h"

static void send_current_player(server_t *server, player_t *gui)
{
    player_t *player;

    SLIST_FOREACH(player, &server->head_players, next) {
        if (player->type != AI)
            continue;
        add_to_gui_buffer(gui, "pnw %d %d %d %d %d %s\n", player->id,
            player->x, player->y,
            player->direction, player->level, player->team);
            send_inv(gui, player);
        add_to_gui_buffer(gui, "plv %d %d\n", player->id, player->level);
    }
}

void start_gui(server_t *server, player_t *gui)
{
    parsing_t *opt = server->options;
    egg_t *egg;

    gui->type = GUI;
    add_to_gui_buffer(gui, "msz %d %d\nsgt %d\n",
        opt->width, opt->height, opt->frequence);
    send_map(server, gui);
    send_teams(server, gui, NULL);
    send_current_player(server, gui);
    SLIST_FOREACH(egg, &server->head_eggs, next) {
        add_to_gui_buffer(gui, "enw %d %d %d %d\n",
            egg->id, egg->player_id, egg->x, egg->y);
        add_to_gui_buffer(gui, "eht %d\n", egg->id);
    }
    send_buffer(gui);
}
