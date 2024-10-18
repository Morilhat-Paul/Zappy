/*
** EPITECH PROJECT, 2024
** server
** File description:
** command
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "command.h"
#include "struct_server.h"
#include "struct_player.h"
#include "struct_command.h"

void enqueue_command(player_t *player, const command_t *command)
{
    int i = 0;

    for (i = 0; player->commands[i]; i++);
    if (i == MAX_COMMAND)
        return;
    player->commands[i] = command;
    clock_gettime(CLOCK_MONOTONIC, &player->cmd_start);
}

void dequeue_command(player_t *player, const command_t *command)
{
    const command_t **commands = player->commands;
    bool cmd_find = false;

    for (int i = 0; commands[i]; i++) {
        if (commands[i] == command) {
            commands[i] = commands[i + 1];
            cmd_find = true;
        }
        if (cmd_find)
            commands[i] = commands[i + 1];
    }
}

void clear_commands(player_t *player)
{
    const command_t **commands = player->commands;

    for (int i = 0; commands[i]; i++)
        commands[i] = NULL;
}

#include "incantation.h"
#include "send_message.h"

static bool TEST(server_t *server, player_t *player)
{
    player_t *player_it = NULL;
    const tile_t *tile = &server->map[player->y][player->x];
    const int level = player->level - 1;
    unsigned int player_nb = 0;

    for (int res = 1; res < 6; res++) {
        if (tile->resources[res].quantity < resources_level[level][res]) {
            // send_to(player->socket, "ko\n");
            return false;
        }
    }
    SLIST_FOREACH(player_it, &server->head_players, next) {
        if ((player_it->x == player->x) && (player_it->y == player->y))
            player_nb++;
    }
    if (player_nb < resources_level[level][0]) {
        // send_to(player->socket, "ko\n");
        return false;
    }
    send_to(player->socket, "Elevation underway\n");
    return true;
}

static bool is_incantate = false;

void execute_commands(server_t *server, player_t *player)
{
    const command_t **commands = player->commands;
    const char **args = NULL;
    double trigger = NO_TIME_LIMIT;
    double diff = 0.0;
    struct timespec tend = { 0, 0 };
    bool is_okay = true;

    for (int i = 0; commands[i]; i++) {
        is_okay = true;
        trigger += commands[i]->time;
        trigger /= server->options->frequence;
        trigger *= 1000;
        clock_gettime(CLOCK_MONOTONIC, &tend);
        diff = ((tend.tv_sec * 1e9) + tend.tv_nsec);
        diff -= ((player->cmd_start.tv_sec * 1e9) + player->cmd_start.tv_nsec);
        diff /= 1e6;
        if (!is_incantate && strncmp(commands[i]->name, "Incantation", 11) == 0) {
            is_okay = TEST(server, player);
            is_incantate = true;
        }
        if (!is_okay) {
            send_to(player->socket, "ko\n");
            return;
        }
        if ((commands[i]->time != NO_TIME_LIMIT) && (diff < trigger))
            return;
        args = commands[i]->args;
        commands[i]->function(server, player, args);
        if (is_incantate && strncmp(commands[i]->name, "Incantation", 11) == 0)
            is_incantate = false;
        dequeue_command(player, commands[i]);
        clock_gettime(CLOCK_MONOTONIC, &player->cmd_start);
    }
}

command_t *create_command(
    const char *name,
    const char **args,
    unsigned int time,
    command_function_t function)
{
    command_t *command = malloc(sizeof(command_t));

    if (command == NULL) {
        perror("malloc() failed");
        return NULL;
    }
    command->name = name;
    command->args = args;
    command->time = time;
    command->function = function;
    return command;
}
