/*
** EPITECH PROJECT, 2024
** server
** File description:
** struct_server
*/

#ifndef STRUCT_SERVER_H_
    #define STRUCT_SERVER_H_

    #include <stdbool.h>
    #include <sys/select.h>

    #include "logger.h"
    #include "struct_network_infos.h"
    #include "struct_player.h"
    #include "struct_tile.h"
    #include "parsing.h"

/* Server structure */
typedef struct server_s {
    parsing_t *options;
    network_infos_t *network_infos;
    fd_set master_set;
    fd_set working_set;
    int nb_connection;
    int max_sockfd;
    SLIST_HEAD(Client, player_s) head_players;
    SLIST_HEAD(Egg, egg_s) head_eggs;
    int players_connected;
    tile_t **map;
    struct timespec generate_res;
    bool running;
} server_t;

#endif /* !STRUCT_SERVER_H_ */
