/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** struct_tile
*/

#ifndef STRUCT_TILE_H_
    #define STRUCT_TILE_H_

    #include "resources.h"

typedef struct tile_s {
    unsigned int x;                                 // Tile's x position
    unsigned int y;                                 // Tile's y position
    resource_quantity_t resources[NB_RESOURCE];     // Tile's ressources
} tile_t;

#endif /* !STRUCT_TILE_H_ */
