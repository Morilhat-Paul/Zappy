/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** logs.cpp
*/

#include "../include/logs.hpp"
#include <iostream>

Logs::Logs(const std::string& filename) {
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file: " << filename << std::endl;
    }
}

Logs::~Logs() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logs::log(const std::string& message) {
    if (logFile.is_open()) {
        logFile << getCurrentTime() << " - " << message << std::endl;
    }
}

void Logs::logReceivedMessage(const std::string& message) {
    log("Received: " + message);
}

void Logs::logSentMessage(const std::string& message) {
    log("Sent: " + message);
}

std::string Logs::getCurrentTime() {
    std::time_t now = std::time(nullptr);
    char buf[80];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return buf;
}
