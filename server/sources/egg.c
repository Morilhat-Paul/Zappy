/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** egg
*/

#include <time.h>
#include "player.h"
#include "gui.h"
#include "send_message.h"

static void insert_to_tail(server_t *server, egg_t *egg)
{
    egg_t *tmp = NULL;

    if (SLIST_EMPTY(&server->head_eggs)) {
        SLIST_INSERT_HEAD(&server->head_eggs, egg, next);
    } else {
        tmp = SLIST_FIRST(&server->head_eggs);
        while (SLIST_NEXT(tmp, next) != NULL) {
            tmp = SLIST_NEXT(tmp, next);
        }
        SLIST_INSERT_AFTER(tmp, egg, next);
    }
}

void create_new_egg(server_t *server, player_t *player)
{
    static int egg_id = 0;
    egg_t *egg = malloc(sizeof(egg_t));

    if (!player) {
        egg->player_id = -1;
        egg->x = rand() % server->options->width;
        egg->y = rand() % server->options->height;
    } else {
        egg->player_id = player->id;
        egg->x = player->x;
        egg->y = player->y;
    }
    egg->id = egg_id;
    add_to_all_gui(server, "enw %d %d %d %d\n", egg_id, egg->player_id,
        egg->x, egg->y);
    insert_to_tail(server, egg);
    egg_id++;
}

void init_egg(server_t *server)
{
    srand(time(NULL));
    for (int i = 0; i < server->options->clientsNb; i++)
        create_new_egg(server, NULL);
}

void hatch_new_player(server_t *server, player_t *player, char *name)
{
    egg_t *np;
    int len;

    if (!SLIST_EMPTY(&server->head_eggs)) {
        np = SLIST_FIRST(&server->head_eggs);
        SLIST_REMOVE_HEAD(&server->head_eggs, next);
        len = strlen(name);
        player->type = AI;
        player->team = malloc(sizeof(char) * (len + 1));
        strcpy(player->team, name);
        player->id = np->id;
        player->x = np->x;
        player->y = np->y;
        send_to(player->socket, "%d\n%d %d\n",
            server->options->clientsNb -server->nb_connection,
            server->options->width, server->options->height);
        new_ai_logged(server, player);
        free(np);
    } else
        send_message(player->socket, "ko\n");
}

void destroy_egg(server_t *server)
{
    egg_t *egg;

    while (!SLIST_EMPTY(&server->head_eggs)) {
        egg = SLIST_FIRST(&server->head_eggs);
        SLIST_REMOVE_HEAD(&server->head_eggs, next);
        free(egg);
    }
}
