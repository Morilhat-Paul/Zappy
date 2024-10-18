/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** tile
*/

#include "tile.h"
#include "resources.h"
#include <stdio.h>

void print_tile(const tile_t *tile)
{
    printf("Tile: [%d][%d]\n", tile->x, tile->y);
    for (int i = 0; i < NB_RESOURCE; i++)
        print_resource_quantity(tile->resources[i]);
}
