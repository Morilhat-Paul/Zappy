/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** resources
*/

#include <stdio.h>
#include "resources.h"
#include "struct_server.h"

void print_resource_quantity(const resource_quantity_t resource_quantity)
{
    printf("%s: %d\n", resource_quantity.name, resource_quantity.quantity);
}

static void init_resource(server_t *server, int ressource)
{
    int x = 0;
    int y = 0;

    x = random() % server->options->width;
    y = random() % server->options->height;
    server->map[y][x].resources[ressource].quantity++;
}

int get_max_resource(const resource_t resource, const int area)
{
    return resources_density[resource].density * area;
}

static void init_tile(tile_t *tile)
{
    for (int i = 0; i < NB_RESOURCE; i++) {
        tile->resources[i].resource = resources_density[i].ressource;
        tile->resources[i].name = resources_density[i].name;
    }
}

void init_resources(server_t *server)
{
    const int area = server->options->width * server->options->height;
    resource_quantity_t max_resource_quantity[] = {
        { "food", food, get_max_resource(food, area) },
        { "linemate", linemate, get_max_resource(linemate, area) },
        { "deraumere", deraumere, get_max_resource(deraumere, area) },
        { "sibur", sibur, get_max_resource(sibur, area) },
        { "mendiane", mendiane, get_max_resource(mendiane, area) },
        { "phiras", phiras, get_max_resource(phiras, area) },
        { "thystame", thystame, get_max_resource(thystame, area) },
    };

    for (int i = 0; i < server->options->height; i++)
        for (int j = 0; j < server->options->width; j++) {
            server->map[i][j].x = j;
            server->map[i][j].y = i;
            init_tile(&server->map[i][j]);
        }
    for (int i = 0; i < NB_RESOURCE; i++)
        for (unsigned int j = 0; j < max_resource_quantity[i].quantity; j++)
            init_resource(server, i);
}

static void get_global_ressources(tile_t *tile,
    resource_quantity_t *global_quantity)
{
    for (int i = 0; i < NB_RESOURCE; i++)
        if (global_quantity[i].quantity > 0)
            global_quantity[i].quantity -= tile->resources[i].quantity;
}

static void regenerate_ressources(server_t *server)
{
    parsing_t *opt = server->options;
    const int area = opt->width * opt->height;
    resource_quantity_t global_quantity[] = {
        { "food", food, get_max_resource(food, area) },
        { "linemate", linemate, get_max_resource(linemate, area) },
        { "deraumere", deraumere, get_max_resource(deraumere, area) },
        { "sibur", sibur, get_max_resource(sibur, area) },
        { "mendiane", mendiane, get_max_resource(mendiane, area) },
        { "phiras", phiras, get_max_resource(phiras, area) },
        { "thystame", thystame, get_max_resource(thystame, area) },
    };

    for (int i = 0; i < server->options->height; i++)
        for (int j = 0; j < server->options->width; j++)
            get_global_ressources(&server->map[i][j], &global_quantity[0]);
    for (int i = 0; i < NB_RESOURCE; i++)
        for (unsigned int j = 0; j < global_quantity[i].quantity; j++)
            init_resource(server, i);
}

void ressource_timer(server_t *server)
{
    double trigger = RESOURCE_SPAWN_TIME;
    double diff = 0.0;
    struct timespec tend = { 0, 0 };

    clock_gettime(CLOCK_MONOTONIC, &tend);
    trigger /= server->options->frequence;
    diff = ((tend.tv_sec * 1e9) + tend.tv_nsec);
    diff -= ((server->generate_res.tv_sec * 1e9) +
        server->generate_res.tv_nsec);
    if ((diff / 1e6) >= (trigger * 1e3)) {
        regenerate_ressources(server);
        clock_gettime(CLOCK_MONOTONIC, &server->generate_res);
    }
}
