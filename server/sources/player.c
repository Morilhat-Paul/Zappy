/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** player
*/


#include "player.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include "send_message.h"

static void init_player_value(player_t *player, const int id, const int socket)
{
    player->socket = socket;
    player->id = id;
    player->level = 1;
    player->direction = 1 + rand() % 4;
    clock_gettime(CLOCK_MONOTONIC, &player->cmd_start);
    clock_gettime(CLOCK_MONOTONIC, &player->eat_time);
    player->resources[food].quantity = 9;
}

player_t *player_create(int id, int socket)
{
    player_t *player = calloc(1, sizeof(player_t));
    socklen_t addr_len = sizeof(player->addr);
    char client_ip[INET_ADDRSTRLEN] = { 0 };

    if (player == NULL) {
        perror("malloc() failed");
        return NULL;
    }
    if (getpeername(socket, (SA *)&player->addr, &addr_len) == -1) {
        perror("getpeername");
        return NULL;
    }
    inet_ntop(AF_INET, &(player->addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    init_player_value(player, id, socket);
    return player;
}

player_t *get_player_from_id(const server_t *server, const int id)
{
    player_t *player;

    SLIST_FOREACH(player, &server->head_players, next)
        if (player->id == id)
            return player;
    return NULL;
}

player_type_t get_player_type(const char *msg)
{
    if (strncmp(msg, GRAPHIC_TEAM_NAME, strlen(GRAPHIC_TEAM_NAME)) == 0)
        return GUI;
    else
        return AI;
}

void player_disconnection(server_t *server, const player_t *player)
{
    char client_ip[INET_ADDRSTRLEN] = { 0 };
    int client_port = 0;
    char *type = NULL;

    inet_ntop(AF_INET, &(player->addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    client_port = ntohs(player->addr.sin_port);
    if (player->type == AI) {
        type = "AI";
        add_to_all_gui(server, "pdi %d\n", player->id);
    } else if (player->type == GUI)
        type = "GUI";
    else
        type = "UNKNOWN";
    close(player->socket);
    printf("/===========Closing client===========\\\n");
    printf(" ================USER===============\n");
    printf(" %s:%d\n", client_ip, client_port);
    printf(" Type = %s\n", type);
    printf(" ===================================\n");
    printf("\\====================================/\n");
}

void player_disconnection_all(server_t *server)
{
    player_t *player;

    while (!SLIST_EMPTY(&server->head_players)) {
        player = SLIST_FIRST(&server->head_players);
        SLIST_REMOVE_HEAD(&server->head_players, next);
        player_disconnection(server, player);
        server->players_connected--;
        if (player->type == AI)
            free(player->team);
        free(player);
    }
}
