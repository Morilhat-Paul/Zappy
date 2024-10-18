/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** logger.h
*/

#ifndef LOGGER_H
    #define LOGGER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #define INFO_FILE "INFO.log"
    #define DEBUG_FILE "DEBUG.log"
    #define ERROR_FILE "ERROR.log"
    #define LOG_BUFFER_SIZE 1024
    #define TIMESTAMP_FORMAT "%Y-%m-%d %H:%M:%S"
    #define TIMESTAMP_SIZE 20

typedef enum log_level_s {
    INFO = 0,
    DEBUG,
    ERROR
} log_level_t;

typedef struct logger_s {
    void (*log)(const char *format, ...);
    void (*error)(const char *format, ...);
    void (*debug)(const char *format, ...);
} logger_t;

void log_message(const char *format, ...);
void log_error(const char *format, ...);
void log_debug(const char *format, ...);

extern logger_t logger;

#endif /*LOGGER_H*/
