/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** look
*/

#include "command_functions.h"
#include "struct_player.h"
#include "struct_server.h"
#include "send_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"

static int get_north(server_t *server, int sq)
{
    sq -= server->options->width;
    if (sq < 0)
        sq += server->options->width * server->options->height;
    return sq;
}

static int get_south(server_t *server, int sq)
{
    sq += server->options->width;
    if (sq >= server->options->width * server->options->height)
        sq -= server->options->width * server->options->height;
    return sq;
}

static int get_east(server_t *server, int sq)
{
    sq++;
    if (sq % server->options->width == 0)
        sq -= server->options->width;
    return sq;
}

static int get_west(server_t *server, int sq)
{
    if (sq % server->options->width == 0)
        sq += server->options->width;
    sq--;
    return sq;
}

int get_top_left(server_t *server, int sq, direction_t dir)
{
    switch (dir) {
    case N:
        return get_west(server, get_north(server, sq));
    case S:
        return get_east(server, get_south(server, sq));
    case E:
        return get_north(server, get_east(server, sq));
    case W:
        return get_south(server, get_west(server, sq));
    default:
        return -1;
    }
}

int get_right(server_t *server, int sq, direction_t dir)
{
    switch (dir) {
    case N:
        return get_east(server, sq);
    case S:
        return get_west(server, sq);
    case E:
        return get_south(server, sq);
    case W:
        return get_north(server, sq);
    default:
        return -1;
    }
}

static void get_tile_entity(server_t *server, char **s, tile_t *tile)
{
    player_t *player;
    egg_t *egg;

    SLIST_FOREACH(player, &server->head_players, next) {
        if (PLAYER_IS_AI(player) &&
            player->x == (int)tile->x && player->y == (int)tile->y) {
            *s = realloc(*s, (strlen(*s) + 7 + 1));
            strcat(*s, " player");
        }
    }
    SLIST_FOREACH(egg, &server->head_eggs, next) {
        if (egg->x == (int)tile->x && egg->y == (int)tile->y) {
            *s = realloc(*s, (strlen(*s) + 4 + 1));
            strcat(*s, " egg");
        }
    }
}

void add_tile_content(server_t *server, char **s, tile_t *tile)
{
    get_tile_entity(server, s, tile);
    for (int i = 0; i < NB_RESOURCE; ++i) {
        if (tile->resources[i].quantity == 0)
            continue;
        if ((*s)[strlen(*s) - 1] != ' ') {
            *s = realloc(*s, strlen(*s) + 2);
            strcat(*s, " ");
        }
        *s = realloc(*s, strlen(*s) + strlen(tile->resources[i].name) + 1);
        strcat(*s, tile->resources[i].name);
    }
}

void get_content(server_t *server, player_t *player, int first_sq, char **s)
{
    int i = 0;
    int j;
    int sq;
    tile_t *tile;

    while (i < player->level + 1) {
        sq = first_sq;
        j = 0;
        while (j < (i * 2 + 1)) {
            tile = &server->map[sq / server->options->width][sq %
            server->options->width];
            add_tile_content(server, s, tile);
            *s = realloc(*s, strlen(*s) + 2);
            strcat(*s, ",");
            sq = get_right(server, sq, player->direction);
            j++;
        }
        first_sq = get_top_left(server, first_sq, player->direction);
        i++;
    }
}

void function_look(server_t *server, player_t *player, const char **)
{
    char *s = malloc(sizeof(char) * 1);
    int first_sq = player->y * server->options->width + player->x;

    s[0] = '\0';
    get_content(server, player, first_sq, &s);
    s[strlen(s)] = '\0';
    send_to(player->socket, "[%s]\n", s + 1);
}
