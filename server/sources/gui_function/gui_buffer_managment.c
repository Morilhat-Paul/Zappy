/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** gui_buffer_managment
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "send_message.h"
#include "gui.h"

void send_buffer(player_t *gui)
{
    if (strlen(gui->response) > 0) {
        send_to(gui->socket, gui->response);
        gui->response[0] = '\0';
    }
}

static void safe_add(player_t *gui, char *msg)
{
    if ((strlen(gui->response) + strlen(msg) >= GUI_MAX_BUFFER))
        send_buffer(gui);
    strcat(gui->response, msg);
}

void add_to_gui_buffer(player_t *gui, const char *format, ...)
{
    va_list args;
    char *msg = NULL;
    int len = 0;

    va_start(args, format);
    len = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);
    msg = (char *)calloc(len, sizeof(char));
    if (msg == NULL) {
        perror("calloc");
        return;
    }
    va_start(args, format);
    vsnprintf(msg, len, format, args);
    va_end(args);
    safe_add(gui, msg);
    free(msg);
}

static void add_to_all(const server_t *server, char *msg)
{
    player_t *gui;

    SLIST_FOREACH(gui, &server->head_players, next) {
        if (PLAYER_IS_GUI(gui))
            safe_add(gui, msg);
    }
}

void add_to_all_gui(const server_t *server, const char *format, ...)
{
    va_list args;
    char *msg = NULL;
    int len = 0;

    va_start(args, format);
    len = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);
    msg = (char *)calloc(len, sizeof(char));
    if (msg == NULL) {
        perror("calloc");
        return;
    }
    va_start(args, format);
    vsnprintf(msg, len, format, args);
    va_end(args);
    add_to_all(server, msg);
    free(msg);
}
