/*
** EPITECH PROJECT, 2024
** server
** File description:
** socket
*/


#include "socket.h"

void socket_set_options(server_t *server, int on)
{
    int value = setsockopt(server->network_infos->sockfd,
        SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    if (value < 0) {
        perror("setsockopt() failed");
        close(server->network_infos->sockfd);
        exit(84);
    }
}

void socket_create(server_t *server)
{
    int value = 0;
    int on = 1;

    server->network_infos->sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server->network_infos->sockfd < 0) {
        perror("socket() failed");
        exit(84);
    }
    socket_set_options(server, on);
    value = ioctl(server->network_infos->sockfd, FIONBIO, &on);
    if (value < 0) {
        perror("ioctl() failed");
        close(server->network_infos->sockfd);
        exit(84);
    }
}

void socket_bind(server_t *server)
{
    int value = 0;
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(server->network_infos->ip);
    addr.sin_port = htons(server->network_infos->port);
    value = bind(server->network_infos->sockfd, (SA *)&addr, sizeof(addr));
    if (value < 0) {
        perror("bind() failed");
        close(server->network_infos->sockfd);
        exit(84);
    }
}
