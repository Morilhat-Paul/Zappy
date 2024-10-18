/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include "../include/network.hpp"
#include "../include/gui.hpp"

int main(int argc, char **argv)
{
    std::string ip;
    unsigned short port = 0;

    int opt;
    while ((opt = getopt(argc, argv, "h:p:")) != -1) {
        switch (opt) {
            case 'h':
                ip = optarg;
                break;
            case 'p':
                port = static_cast<unsigned short>(std::stoi(optarg));
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -h <ip> -p <port>" << std::endl;
                return -1;
        }
    }

    if (ip.empty() || port == 0) {
        std::cerr << "Usage: " << argv[0] << " -h <ip> -p <port>" << std::endl;
        return -1;
    }

    Network network(ip, port);
    if (!network.connect()) {
        return -1;
    }

    GUI gui(network);
    gui.run();

    return 0;
}
