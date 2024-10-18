/*
** EPITECH PROJECT, 2024
** server
** File description:
** struct_network_infos
*/

#ifndef STRUCT_NETWORK_INFOS_H_
    #define STRUCT_NETWORK_INFOS_H_

    #include <arpa/inet.h>
    #include <netinet/in.h>

/* All network infos that the server needs */
typedef struct network_infos_s {
    char ip[INET_ADDRSTRLEN];   // IP string of the server
    unsigned int port;          // Port of the server
    // struct sockaddr_in addr;
    int sockfd;                 // Socket of the server
} network_infos_t;

#endif /* !STRUCT_NETWORK_INFOS_H_ */
