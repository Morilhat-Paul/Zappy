/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** map
*/

#include "gui.h"
#include "player.h"
#include "resources.h"
#include "send_message.h"

void send_tile_to_all(server_t *server, int x, int y)
{
    const parsing_t *opt = server->options;
    char str[1024];
    char buffer[20];

    if (x >= opt->width || y >= opt->height)
        return;
    sprintf(str, "bct %d %d", x, y);
    for (int i = 0; i < NB_RESOURCE; i++) {
        sprintf(buffer, " %d", server->map[y][x].resources[i].quantity);
        strcat(str, buffer);
    }
    add_to_all_gui(server, "%s\n", str);
}

static void send_tile(server_t *server, player_t *gui, int x, int y)
{
    const parsing_t *opt = server->options;
    char str[1024];
    char buffer[20];

    if (x >= opt->width || y >= opt->height)
        return;
    sprintf(str, "bct %d %d", x, y);
    for (int i = 0; i < NB_RESOURCE; i++) {
        sprintf(buffer, " %d", server->map[y][x].resources[i].quantity);
        strcat(str, buffer);
    }
    strcat(str, "\n");
    strcat(gui->response, str);
}

void tile(server_t *server, player_t *gui, char **args)
{
    if (!args || !args[1]) {
        return;
    }
    send_tile(server, gui, atoi(args[0]), atoi(args[1]));
}

void send_map(server_t *server, player_t *gui)
{
    for (int i = 0; i < server->options->width; i++)
        for (int j = 0; j < server->options->height; j++)
            send_tile(server, gui, i, j);
}
