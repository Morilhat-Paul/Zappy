/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** resources
*/

#ifndef RESOURCES_H_
    #define RESOURCES_H_

    #define NB_RESOURCE 7
    #define RESOURCE_SPAWN_TIME 20
    #define FOOD_TIME_SURVIVE 126
    #define RESOURCE_QUANTITY(x, y, res) x * y * resources_density[res].density

typedef enum resource_e {
    food = 0,
    linemate,
    deraumere,
    sibur,
    mendiane,
    phiras,
    thystame,
    egg,
    player,
    invalid_resource = -1
} resource_t;

typedef struct ressource_density_s {
    char *name;
    resource_t ressource;
    float density;
} resource_density_t;

typedef struct resource_quantity_s {
    char *name;
    resource_t resource;     // The resource
    unsigned int quantity;   // Quantity of the resource
} resource_quantity_t;

static const resource_density_t resources_density[] = {
    { "food", food, 0.5 },
    { "linemate", linemate, 0.3 },
    { "deraumere", deraumere, 0.15 },
    { "sibur", sibur, 0.1 },
    { "mendiane", mendiane, 0.1 },
    { "phiras", phiras, 0.08 },
    { "thystame", thystame, 0.05 },
};

typedef struct server_s server_t;

void print_resource_quantity(resource_quantity_t resource_quantity);
void init_resources(server_t *server);
resource_t parse_resource(const char *resource_name);
void ressource_timer(server_t *server);

#endif /* !RESOURCES_H_ */
