/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** direction
*/

#ifndef DIRECTION_H_
    #define DIRECTION_H_

typedef enum direction_e {
    S = 1,
    E = 2,
    N = 3,
    W = 4,
} direction_t;

const char *direction_to_str(const direction_t direction);

#endif /* !DIRECTION_H_ */
