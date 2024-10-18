/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** gui
*/

#ifndef GUI_H_
    #define GUI_H_

    #include "player.h"
    #include "resources.h"

void start_gui(server_t *server, player_t *gui);
void tile(server_t *server, player_t *gui, char **args);
void send_map(server_t *server, player_t *gui);
void send_buffer(player_t *gui);
void send_teams(server_t *server, player_t *gui, const char **);
void send_inv(player_t *gui, player_t *player);
void send_inv_to_all_gui(server_t *server, player_t *player);
void player_inv(server_t *server, player_t *gui, const char **args);
void new_ai_logged(server_t *server, player_t *player);
void send_tile_to_all(server_t *server, int x, int y);

#endif /* !GUI_H_ */
