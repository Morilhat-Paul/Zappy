/*
** EPITECH PROJECT, 2024
** server
** File description:
** command
*/

#ifndef COMMAND_H_
    #define COMMAND_H_

    #include "command_functions.h"
    #include "struct_command.h"
    #include <stdlib.h>

    #define MAX_COMMAND 10
    #define TIME_LIMIT(t, f) t / f
    #define NO_TIME_LIMIT 0

static const command_t client_commands[] = {
    { "Noop", NULL, NO_TIME_LIMIT, &function_noop },
    { "Forward", NULL, 7, &function_forward },
    { "Right", NULL, 7, &function_right },
    { "Left", NULL, 7, &function_left },
    { "Look", NULL, 7, &function_look },
    { "Inventory", NULL, 1, &function_inventory },
    { "Broadcast", NULL, 7, &function_broadcast },
    { "Connect_nbr", NULL, NO_TIME_LIMIT, &function_connectnbr },
    { "Fork", NULL, 42, &function_fork },
    { "Eject", NULL, 7, &function_eject },
    { "Take", NULL, 7, &function_take },
    { "Set", NULL, 7, &function_set },
    { "Incantation", NULL, 300, &function_incantation },
};

static const int nb_client_cmd =
sizeof(client_commands) / sizeof(client_commands[0]);

/* Player structure */
typedef struct player_s player_t;

/**
 * Adds a command to a player's queue.
 * If the queue is full, the order is not added.
 *
 * @param player A pointer to the player structure.
 * @param command A pointer to the command to be added to the queue.
 */
void enqueue_command(player_t *player, const command_t *command);

/**
 * Removes a specific command from a player's command queue, if it exists.
 *
 * @param player A pointer to the structure representing the player.
 * @param command A pointer to the command to remove from the command queue.
 */
void dequeue_command(player_t *player, const command_t *command);

/**
 * Executes all commands in a player's command queue.
 *
 * @param player A pointer to the structure representing the player.
 */
void execute_commands(server_t *server, player_t *player);

/**
 * Clears all commands from a player's command queue.
 *
 * @param player A pointer to the structure representing the player.
 */
void clear_commands(player_t *player);

/**
 * Clears all commands from a player's command queue.
 *
 * @param name Name of the command.
 * @param args Arguments of the command.
 * @param time Time of the command.
 * @param function Function of the command.
 * @return A 'command_t' structure
 */
command_t *create_command(
    const char *name,
    const char **args,
    const unsigned int time,
    command_function_t function);

#endif /* !COMMAND_H_ */
