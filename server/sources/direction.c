/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** direction
*/

#include "direction.h"

const char *direction_to_str(const direction_t direction)
{
    switch (direction) {
        case N:
            return "North";
        case S:
            return "South";
        case E:
            return "East";
        case W:
            return "West";
        default:
            return "Unknown";
    }
}
