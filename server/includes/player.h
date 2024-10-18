/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include <stdbool.h>
    #include "struct_player.h"
    #include "struct_server.h"

    #define SA struct sockaddr
    #define GRAPHIC_TEAM_NAME "GRAPHIC"
    #define PLAYER_IS_AI(player) ((player)->type == AI)
    #define PLAYER_IS_GUI(player) ((player)->type == GUI)

player_t *player_create(int id, int socket);
player_t *get_player_from_id(const server_t *server, const int id);
player_type_t get_player_type(const char *msg);
void player_disconnection(server_t *server, const player_t *player);
void player_disconnection_all(server_t *server);
void init_egg(server_t *server);
void create_new_egg(server_t *server, player_t *player);
void hatch_new_player(server_t *server, player_t *player, char *name);
void destroy_egg(server_t *server);
void check_limits(server_t *server, player_t *player);

#endif /* !PLAYER_H_ */
