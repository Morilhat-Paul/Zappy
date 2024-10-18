/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** logs.hpp
*/

#ifndef LOGS_HPP
    #define LOGS_HPP

#include <fstream>
#include <string>
#include <ctime>

class Logs {
public:
    Logs(const std::string& filename);
    ~Logs();
    
    void log(const std::string& message);
    void logReceivedMessage(const std::string& message);
    void logSentMessage(const std::string& message);
    
private:
    std::ofstream logFile;
    
    std::string getCurrentTime();
};

#endif // LOGS_HPP
