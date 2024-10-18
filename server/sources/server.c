/*
** EPITECH PROJECT, 2024
** server
** File description:
** server
*/

#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "gui.h"
#include "logger.h"
#include "player.h"
#include "resources.h"
#include "server.h"
#include "struct_tile.h"
#include "send_message.h"

static void print_opt_name(const char **name, const int nb_name)
{
    printf("name : [");
    for (int i = 0; i < nb_name; i++) {
        if (i == 0)
            printf("%s", name[i]);
        else
            printf(", %s", name[i]);
    }
    printf("]\n");
}

static void print_server_opt(const parsing_t *options)
{
    printf("===================Zappy Server===================\n");
    printf("port = %d\n", options->port);
    printf("width = %d\n", options->width);
    printf("height = %d\n", options->height);
    printf("clients_nb = %d\n", options->clientsNb);
    printf("freq = %d\n", options->frequence);
    print_opt_name((const char **) options->name, options->nb_name);
    printf("==================================================\n");
}

static void init_server(server_t *server, const char *ip, const parsing_t *opt)
{
    strcpy(&server->network_infos->ip[0], ip);
    server->options = (parsing_t *) opt;
    server->network_infos->port = opt->port;
    server->network_infos->sockfd = 0;
    server->max_sockfd = 0;
    server->nb_connection = 0;
    server->players_connected = 0;
    server->map = (tile_t **) malloc(sizeof(tile_t *) * opt->height);
    for (int y = 0; y < opt->height; y++)
        server->map[y] = (tile_t *) calloc(opt->width, sizeof(tile_t));
    server->running = false;
    print_server_opt(server->options);
}

static void launch_server(server_t *server)
{
    int value = 0;
    network_infos_t *net_infos = server->network_infos;

    socket_create(server);
    socket_bind(server);
    value = listen(net_infos->sockfd, MAX_CONNECTION);
    if (value < 0) {
        perror("listen() failed");
        close(net_infos->sockfd);
        exit(84);
    }
    server->max_sockfd = net_infos->sockfd;
    server->running = true;
    clock_gettime(CLOCK_MONOTONIC, &server->generate_res);
    logger.log("Server listening on %s:%d", net_infos->ip, net_infos->port);
}

static void initialize_sets(server_t *server)
{
    size_t master_set_size = sizeof(server->master_set);

    memcpy(&server->working_set, &server->master_set, master_set_size);
}

static void player_death(server_t *server, player_t *player)
{
    send_message(player->socket, "dead\n");
    player_disconnection(server, (const player_t *) player);
    server->players_connected--;
    create_new_egg(server, player);
    FD_CLR(player->socket, &server->master_set);
    SLIST_REMOVE(&server->head_players, player, player_s, next);
}

void eat(server_t *server, player_t *player)
{
    double trigger = FOOD_TIME_SURVIVE;
    double diff = 0.0;
    struct timespec tend = { 0, 0 };

    clock_gettime(CLOCK_MONOTONIC, &tend);
    trigger /= server->options->frequence;
    diff = ((tend.tv_sec * 1e9) + tend.tv_nsec);
    diff -= ((player->eat_time.tv_sec * 1e9) + player->eat_time.tv_nsec);
    if ((diff / 1e6) < (trigger * 1e3))
        return;
    if (player->resources[food].quantity == 0) {
        player_death(server, player);
        return;
    }
    player->resources[food].quantity -= 1;
    send_inv_to_all_gui(server, player);
    clock_gettime(CLOCK_MONOTONIC, &player->eat_time);
}

void run_server(server_t *server)
{
    player_t *player = NULL;

    initialize_sets(server);
    wait_for_connections(server);
    if (server->nb_connection > 0)
        handle_incoming_connections(server);
    ressource_timer(server);
    SLIST_FOREACH(player, &server->head_players, next) {
        if (PLAYER_IS_AI(player)) {
            eat(server, player);
            execute_commands(server, player);
        }
    }
    player = NULL;
    SLIST_FOREACH(player, &server->head_players, next) {
        if (PLAYER_IS_GUI(player))
            send_buffer(player);
    }
}

static void sig_handler(int __attribute_maybe_unused__)
{
    printf("\n");
}

void server(const parsing_t *options)
{
    server_t server;
    network_infos_t net_infos;

    SLIST_INIT(&server.head_players);
    SLIST_INIT(&server.head_eggs);
    server.network_infos = &net_infos;
    init_server(&server, "127.0.0.1", options);
    init_egg(&server);
    init_resources(&server);
    launch_server(&server);
    FD_ZERO(&server.master_set);
    FD_SET(server.network_infos->sockfd, &server.master_set);
    FD_SET(STDIN_FILENO, &server.master_set);
    signal(SIGINT, &sig_handler);
    clock_gettime(CLOCK_MONOTONIC, &server.generate_res);
    do {
        run_server(&server);
    } while (server.running);
    logger.log("Server shutting down.");
    player_disconnection_all(&server);
}
