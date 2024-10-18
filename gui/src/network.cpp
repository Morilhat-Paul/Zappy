/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** network.cpp
*/

#include "../include/network.hpp"
#include <iostream>
#include <sstream>

Network::Network(const std::string& address, unsigned short port)
    : serverAddress(address), serverPort(port), logs("network.log") {}

bool Network::connect() {
    if (socket.connect(serverAddress, serverPort) == sf::Socket::Done) {
        std::cout << "Connected to the server." << std::endl;
        logs.log("Connected to the server.");
        return true;
    }
    std::cout << "Failed to connect to the server." << std::endl;
    logs.log("Failed to connect to the server.");
    return false;
}

void Network::disconnect() {
    socket.disconnect();
    logs.log("Disconnected from the server.");
}

bool Network::isConnected() const {
    return socket.getRemoteAddress() != sf::IpAddress::None;
}

bool Network::sendMessage(const std::string& message) {
    if (socket.send(message.c_str(), message.size()) != sf::Socket::Done) {
        std::cout << "Failed to send message." << std::endl;
        logs.log("Failed to send message: " + message);
        return false;
    }
    logs.logSentMessage(message);
    return true;
}

bool Network::receiveMessages(std::queue<std::string>& messages) {
    char buffer[40960];
    std::size_t received;
    sf::Socket::Status status = socket.receive(buffer, sizeof(buffer), received);
    if (status == sf::Socket::Disconnected) {
        std::cout << "Server disconnected." << std::endl;
        logs.log("Server disconnected.");
        exit(0);
    } else if (status != sf::Socket::Done) {
        if (status != sf::Socket::NotReady) {
            std::cout << "Receive error: " << status << std::endl;
            logs.log("Receive error: " + std::to_string(status));
        }
        return true;
    }
    std::istringstream stream(std::string(buffer, received));
    std::string line;
    while (std::getline(stream, line)) {
        messages.push(line);
        logs.logReceivedMessage(line);
    }
    return true;
}

void Network::registerHandler(const std::string& type, std::function<void(const std::string&)> handler) {
    handlers[type] = handler;
}

void Network::handleMessage(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    stream >> type;
    auto it = handlers.find(type);
    if (it != handlers.end()) {
        it->second(message);
    } else {
        std::cerr << "No handler for message type: " << type << std::endl;
    }
}
