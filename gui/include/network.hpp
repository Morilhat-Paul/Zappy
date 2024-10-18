/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** network.hpp
*/

#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <SFML/Network.hpp>
#include "logs.hpp"
#include <string>
#include <queue>
#include <functional>
#include <unordered_map>

class Network {
public:
    Network(const std::string& address, unsigned short port);
    bool connect();
    void disconnect();
    bool isConnected() const;
    bool sendMessage(const std::string& message);
    bool receiveMessages(std::queue<std::string>& messages);
    void processMessages();

    using MessageHandler = std::function<void(const std::string&)>;
    void registerHandler(const std::string& messageType, MessageHandler handler);

private:
    sf::TcpSocket socket;
    sf::IpAddress serverAddress;
    unsigned short serverPort;
    std::unordered_map<std::string, MessageHandler> handlers;
    Logs logs;

    void handleMessage(const std::string& message);
};

#endif // NETWORK_HPP
