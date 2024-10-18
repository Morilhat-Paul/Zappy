/*
** EPITECH PROJECT, 2024
** server
** File description:
** connexion
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "struct_player.h"
#include "connexion.h"
#include "message.h"
#include "command.h"
#include "player.h"
#include "send_message.h"
#include "tile.h"
#include "gui.h"
#include "split_string.h"

static int get_last_tick(server_t *server)
{
    player_t *player = NULL;
    int last_tick = 1;
    int temp = 0;

    SLIST_FOREACH(player, &server->head_players, next) {
        if (player->commands[0] == NULL)
            continue;
        temp = player->commands[0]->time;
        if (temp < last_tick) {
            last_tick = temp;
        }
    }
    return last_tick;
}

void wait_for_connections(server_t *server)
{
    double last_tick = (get_last_tick(server) / server->options->frequence);
    struct timeval tv = {
        .tv_sec = 0,
        .tv_usec = last_tick * 1e6,
    };

    server->nb_connection = select(
        server->max_sockfd + 1, &server->working_set, NULL, NULL, &tv
    );
    if (server->nb_connection < 0) {
        if (errno == EINTR) {
            server->nb_connection = 0;
            server->running = false;
        } else {
            perror("select() failed");
        }
    }
}

static int accept_connection(server_t *server)
{
    struct sockaddr_in addr;
    char client_ip[INET_ADDRSTRLEN] = { 0 };
    int client_port = 0;
    socklen_t addr_len = sizeof(addr);
    int new_fd = accept(server->network_infos->sockfd, (SA *)&addr, &addr_len);

    if ((new_fd == -1) && (errno != EAGAIN)) {
        perror("accept() failed");
    } else if (new_fd != -1) {
        inet_ntop(AF_INET, &(addr.sin_addr), client_ip, INET_ADDRSTRLEN);
        client_port = ntohs(addr.sin_port);
        printf("Connection from %s:%d\n", client_ip, client_port);
        send_to(new_fd, CONNEXION_SUCCESS);
    }
    return new_fd;
}

static void add_to_master_set(server_t *server, int fd)
{
    FD_SET(fd, &server->master_set);
    if (fd > server->max_sockfd)
        server->max_sockfd = fd;
}

static void handle_server_input(server_t *server)
{
    char *msg = NULL;

    msg = get_server_input(server);
    if (strncmp(msg, "/quit", 5) == 0)
        server->running = false;
    if (msg)
        free(msg);
}

static void handle_client_connection(server_t *server, int socket)
{
    player_t *player = player_create(server->players_connected, socket);

    if (player == NULL)
        return;
    add_to_master_set(server, player->socket);
    SLIST_INSERT_HEAD(&server->head_players, player, next);
    server->players_connected++;
}

static void registeration(server_t *server, player_t *player, const char *msg)
{
    if (get_player_type(msg) == GUI) {
        start_gui(server, player);
        return;
    }
    for (int i = 0; server->options->name[i]; i++)
        if (!strncmp(server->options->name[i], msg, strlen(msg) - 1)) {
            return hatch_new_player(server, player, server->options->name[i]);
        }
    send_to(player->socket, "ko\n");
}

static void handle_client_message(server_t *server, player_t *player)
{
    const char *msg = get_message(server, player);

    if (!msg)
        return;
    if (player->type == UNKNOWN) {
        registeration(server, player, msg);
    } else if (player->type == AI) {
        message_to_ai_cmd(player, msg);
    }
    free((void *) msg);
}

static void handle_client(server_t *server)
{
    player_t *player;

    SLIST_FOREACH(player, &server->head_players, next) {
        if (FD_ISSET(player->socket, &server->working_set))
            handle_client_message(server, player);
    }
}

void handle_incoming_connections(server_t *server)
{
    int new_socket = 0;

    if (FD_ISSET(STDIN_FILENO, &server->working_set))
        handle_server_input(server);
    if (FD_ISSET(server->network_infos->sockfd, &server->working_set)) {
        new_socket = accept_connection(server);
        if (new_socket > 0)
            handle_client_connection(server, new_socket);
    }
    handle_client(server);
}
