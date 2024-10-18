/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tile.hpp
*/

#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "player.hpp"
#include <map>
#include <array>
#include <vector>
#include <memory>

class Tile {
public:
    Tile(float size, int x, int y);
    void setResource(long unsigned int resource, int quantity);
    void addPlayer(const std::shared_ptr<Player>& player);
    void removePlayer(int playerId);
    void addEgg(int eggId);
    void removeEgg(int eggId);
    void draw(sf::RenderWindow& window, sf::Font& font) const;
    std::array<int, 7> getResources() const;

private:
    sf::RectangleShape shape;
    std::vector<std::shared_ptr<Player>> players;
    std::array<int, 7> resources;
    std::vector<int> eggs;
};

#endif // TILE_HPP
