/*
** EPITECH PROJECT, 2024
** server
** File description:
** command_functions
*/

#ifndef COMMAND_FUNCTIONS_H_
    #define COMMAND_FUNCTIONS_H_

typedef struct server_s server_t;
typedef struct player_s player_t;

void function_noop(server_t *server, player_t *player, const char **argv);
void function_forward(server_t *server, player_t *player, const char **av);
void function_right(server_t *server, player_t *player, const char **av);
void function_left(server_t *server, player_t *player, const char **av);
void function_look(server_t *server, player_t *player, const char **av);
void function_inventory(server_t *server, player_t *player, const char **av);
void function_broadcast(server_t *server, player_t *player, const char **av);
void function_connectnbr(server_t *server, player_t *player, const char **av);
void function_eject(server_t *server, player_t *player, const char **av);
void function_fork(server_t *server, player_t *player, const char **av);
void function_take(server_t *server, player_t *player, const char **av);
void function_set(server_t *server, player_t *player, const char **av);
void function_incantation(server_t *server, player_t *player, const char **av);

#endif /* !COMMAND_FUNCTIONS_H_ */
