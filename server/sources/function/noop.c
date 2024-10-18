/*
** EPITECH PROJECT, 2024
** server
** File description:
** noop
*/

#include "command_functions.h"
#include "struct_player.h"
#include "send_message.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void function_noop(server_t *, player_t *player, const char **)
{
    printf("noop\n");
    send_to(player->socket, "ok\n");
}
