/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** broadcast
*/

#include "command_functions.h"
#include "struct_player.h"
#include "struct_server.h"
#include "send_message.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static int handle_major_diff(int *diff)
{
    if (abs(diff[0]) > abs(diff[1]) * 2) {
        if (diff[0] < 0)
            return 3;
        return 7;
    }
    if (abs(diff[1]) > abs(diff[0]) * 2) {
        if (diff[1] < 0)
            return 1;
        return 5;
    }
    return -1;
}

static int handle_minor_diff(int *diff)
{
    if (diff[0] < 0) {
        if (diff[1] < 0)
            return 2;
        return 4;
    }
    if (diff[1] < 0)
        return 8;
    return 6;
}

static int calcul_north_dir(int *diff)
{
    int major_diff_result;

    if (diff[0] == 0 && diff[1] == 0)
        return 0;
    major_diff_result = handle_major_diff(diff);
    if (major_diff_result != -1)
        return major_diff_result;
    return handle_minor_diff(diff);
}

int calculate_diff(int sender_pos, int receiver_pos, int max_value)
{
    int diff = sender_pos - receiver_pos;

    if (abs(diff) > max_value / 2)
        diff = (diff >= 0) ? (max_value - abs(diff)) * -1 :
        (max_value - abs(diff));
    return diff;
}

int adjust_direction(int dir, direction_t receiver_direction)
{
    switch (receiver_direction) {
        case W:
            return (dir <= 2) ? dir + 6 : dir - 2;
        case S:
            return (dir >= 5) ? dir - 4 : dir + 4;
        case E:
            return (dir >= 7) ? dir - 6 : dir + 2;
        default:
            return dir;
    }
}

int get_sound_dir(server_t *server, player_t *receiver, player_t *sender)
{
    int diff[2];
    int dir;

    diff[0] = calculate_diff(sender->x, receiver->x, server->options->width);
    diff[1] = calculate_diff(sender->y, receiver->y, server->options->height);
    dir = calcul_north_dir(diff);
    if (dir == 0)
        return 0;
    return adjust_direction(dir, receiver->direction);
}

void function_broadcast(server_t *server, player_t *player, const char **argv)
{
    player_t *receiver;

    SLIST_FOREACH(receiver, &server->head_players, next) {
        if (receiver->type != AI)
            continue;
        if (receiver != player) {
            int dir = get_sound_dir(server, receiver, player);
            send_to(receiver->socket, "message %d,%s\n", dir, argv[0]);
        }
    }
    add_to_all_gui(server, "pbc %d %s\n", player->id, player->team);
    send_to(player->socket, "ok\n");
}
