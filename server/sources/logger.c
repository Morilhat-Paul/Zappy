/*
** EPITECH PROJECT, 2023
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** logger.c
*/

#include <time.h>
#include <stdarg.h>
#include "logger.h"

static void get_current_timestamp(char *timestamp)
{
    time_t now;

    if (timestamp == NULL)
        return;
    time(&now);
    strftime(timestamp, TIMESTAMP_SIZE, TIMESTAMP_FORMAT, localtime(&now));
}

void log_message(const char *format, ...)
{
    va_list args;
    char timestamp[TIMESTAMP_SIZE] = { 0 };
    char buffer[LOG_BUFFER_SIZE] = { 0 };
    FILE *file = fopen(INFO_FILE, "a");

    if (file == NULL) {
        perror("fopen() failed");
        return;
    }
    get_current_timestamp(&timestamp[0]);
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    fprintf(stdout, "[%s] [INFO]: %s\n", timestamp, buffer);
    fprintf(file, "[%s] [INFO]: %s\n", timestamp, buffer);
    fflush(file);
    fclose(file);
}

void log_error(const char *format, ...)
{
    va_list args;
    char timestamp[TIMESTAMP_SIZE] = { 0 };
    char buffer[LOG_BUFFER_SIZE] = { 0 };
    FILE *file = fopen(ERROR_FILE, "a");

    if (file == NULL) {
        perror("fopen() failed");
        return;
    }
    get_current_timestamp(&timestamp[0]);
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    fprintf(stderr, "[%s] [ERROR]: %s\n", timestamp, buffer);
    fprintf(file, "[%s] [ERROR]: %s\n", timestamp, buffer);
    fflush(file);
    fclose(file);
}

void log_debug(const char *format, ...)
{
    va_list args;
    char timestamp[TIMESTAMP_SIZE] = { 0 };
    char buffer[LOG_BUFFER_SIZE] = { 0 };
    FILE *file = fopen(DEBUG_FILE, "a");

    if (file == NULL) {
        perror("fopen() failed");
        return;
    }
    get_current_timestamp(&timestamp[0]);
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    fprintf(stdout, "[%s] [DEBUG]: %s\n", timestamp, buffer);
    fprintf(file, "[%s] [DEBUG]: %s\n", timestamp, buffer);
    fflush(file);
    fclose(file);
}

logger_t logger = {
    .log = log_message,
    .error = log_error,
    .debug = log_debug
};
