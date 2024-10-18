/*
** EPITECH PROJECT, 2024
** server
** File description:
** struct_command
*/

#ifndef STRUCT_COMMAND_H_
    #define STRUCT_COMMAND_H_

/* Server structure */
typedef struct server_s server_t;

/* Player structure */
typedef struct player_s player_t;

/**
 * @brief Command_function type
 *
 * @param player The player structure
 * @param argv The array of arguments
**/
typedef void (*command_function_t)(
    server_t *server,
    player_t *player,
    const char **argv
);

/* Command structure */
typedef struct command_s {
    const char *name;               // Name of the command
    const char **args;              // Arguments of the command
    int time;                       // Delay of the command
    command_function_t function;    // Function of the command
} command_t;

#endif /* !STRUCT_COMMAND_H_ */
