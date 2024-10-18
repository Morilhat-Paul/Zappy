/*
** EPITECH PROJECT, 2024
** server
** File description:
** struct_player
*/

#ifndef STRUCT_PLAYER_H_
    #define STRUCT_PLAYER_H_

    #include <netinet/in.h>
    #include <stdbool.h>
    #include <sys/queue.h>
    #include <sys/types.h>
    #include <time.h>
    #include "command.h"
    #include "direction.h"
    #include "resources.h"

    #define GUI_MAX_BUFFER 40096

/* Player type */
typedef enum player_type_e {
    UNKNOWN = 0,
    AI,
    GUI
} player_type_t;

/* Egg structure*/
typedef struct egg_s {
    int id;                                     // Egg's ID
    int player_id;                              // Laying player
    int x;                                      // Eggs's x position
    int y;                                      // Egg's y position
    bool hatched;                               // Is egg hatched
    SLIST_ENTRY(egg_s) next;                    // Next elemnt of the list
} egg_t;


/* Player structure */
typedef struct player_s {
    int id;                                     // Player's ID
    int socket;                                 // Player's socket
    player_type_t type;                         // Player's type
    char *team;                                 // Player's team
    const command_t *commands[MAX_COMMAND + 1]; // Player's command queue
    u_int16_t level;                            // Player's level
    direction_t direction;                      // Player's direction
    resource_quantity_t resources[NB_RESOURCE]; // Player's resources
    struct timespec cmd_start;                  // Player's cmd starting time
    struct timespec eat_time;                   // Player's eat time
    int x;                                      // Player's x position
    int y;                                      // Player's y position
    struct sockaddr_in addr;                    // Player's address
    SLIST_ENTRY(player_s) next;                 // Next element of the list
    char response[GUI_MAX_BUFFER];              // GUI buffer
} player_t;

#endif /* !STRUCT_PLAYER_H_ */
