/*
** EPITECH PROJECT, 2024
** B-YEP-400-LYN-4-1-zappy-paul.morilhat
** File description:
** player
*/

#include "network.hpp"
#include "player.hpp"
#include "gui.hpp"

Player::Player(int id, int x, int y) : resources({0, 0, 0, 0, 0, 0, 0}) {
    id_ = id;
    /*shape.setRadius(size);
    shape.setPosition(x * size, y * size);
    shape.setFillColor(sf::Color::Blue);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);*/
}

void Player::setResource(int resource, int quantity) {
    if (resource >= 0 && resource < resources.size()) {
        resources[resource] = quantity;
    }
}
