/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** send_message
*/

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "send_message.h"

void send_message(const int socket, const char *msg)
{
    ssize_t bytes_sent = 0;

    bytes_sent = send(socket, msg, strlen(msg), MSG_NOSIGNAL);
    if (bytes_sent < 0) {
        if ((errno != EPIPE) && (errno != ECONNRESET) && (errno != EBADF))
            perror("send");
    }
}

void send_to(const int socket, const char *format, ...)
{
    va_list args;
    va_list args_copy;
    char *msg = NULL;
    int len = 0;

    va_start(args, format);
    va_copy(args_copy, args);
    len = vsnprintf(NULL, 0, format, args) + 1;
    va_end(args);
    msg = (char *) calloc(len, sizeof(char));
    if (msg == NULL) {
        perror("calloc");
        va_end(args_copy);
        return;
    }
    vsnprintf(msg, len, format, args_copy);
    va_end(args_copy);
    send_message(socket, msg);
    free(msg);
}
