/*
** EPITECH PROJECT, 2024
** server
** File description:
** message
*/

#include "message.h"
#include "player.h"
#include "split_string.h"
#include "send_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "send_message.h"

char *get_server_input(server_t *)
{
    char *buffer = calloc(MAX_INPUT_SIZE, sizeof(char));

    if (read(STDIN_FILENO, buffer, MAX_INPUT_SIZE) < 0)
        perror("read() failed");
    return buffer;
}

char *get_message(server_t *server, player_t *player)
{
    char *buffer = calloc(MAX_MSG_SIZE, sizeof(char));
    ssize_t read_bytes = read(player->socket, buffer, MAX_MSG_SIZE);

    if (read_bytes < 0) {
        perror("read() failed");
        return NULL;
    }
    if (read_bytes == 0) {
        player_disconnection(server, player);
        server->players_connected--;
        FD_CLR(player->socket, &server->master_set);
        SLIST_REMOVE(&server->head_players, player, player_s, next);
        if (player->type == AI)
            free(player->team);
        free(player);
        free(buffer);
        return NULL;
    }
    return buffer;
}

static bool is_command(const char *name, const char *msg)
{
    return (strncmp(name, msg, strlen(name)) == 0);
}

void message_to_ai_cmd(player_t *player, const char *msg)
{
    char **args = NULL;
    int word_count = 0;
    command_t *cmd = NULL;

    for (int i = 0; i < nb_client_cmd; i++) {
        if (is_command(client_commands[i].name, msg)) {
            args = split_string(msg, &word_count);
            args += (word_count > 1) ? 1 : 0;
            cmd = create_command(client_commands[i].name,
                (const char **) args,
                client_commands[i].time,
                client_commands[i].function
            );
            enqueue_command(player, cmd);
            return;
        }
    }
    send_to(player->socket, "ko\n");
}
