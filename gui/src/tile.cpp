/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** tile.cpp
*/

#include "../include/tile.hpp"
#include "../include/player.hpp"
#include "../include/network.hpp"
#include <iostream>

Tile::Tile(float size, int x, int y) : resources({0, 0, 0, 0, 0, 0, 0}) {
    shape.setSize(sf::Vector2f(size, size));
    shape.setPosition(x * size, y * size);
    shape.setFillColor(sf::Color (0, 128, 0, 255));
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1.0f);
}

void Tile::setResource(long unsigned int resource, int quantity) {
    if (resource >= 0 && resource < resources.size()) {
        resources[resource] = quantity;
    }
}

void Tile::addPlayer(const std::shared_ptr<Player>& player) {
    players.push_back(player);
}

void Tile::removePlayer(int playerId) {
    auto it = std::remove_if(players.begin(), players.end(), 
                            [playerId](std::shared_ptr<Player>(player)) {
                                 return player->getId() == playerId;
                            });

    players.erase(it, players.end());
}

void Tile::addEgg(int eggId) {
    eggs.push_back(eggId);
}

void Tile::removeEgg(int eggId) {
    eggs.erase(std::remove(eggs.begin(), eggs.end(), eggId), eggs.end());
}

void Tile::draw(sf::RenderWindow& window, sf::Font& font) const {
    window.draw(shape);

    sf::Text text;
    std::stringstream infoSs;
    text.setFont(font);
    text.setCharacterSize(5);
    text.setFillColor(sf::Color::Black);

    float xOffset = shape.getPosition().x + 1;
    float yOffset = shape.getPosition().y + 1;
    float yStep = 4.5;
    int startY = 20;
    /*static int infoPos = 0;
    for (const auto &player : players)
        infoPos++;*/

    std::array<std::string, 7> resourceNames = {"F", "L", "D", "S", "M", "P", "T"};
    for (long unsigned int i = 0; i < resources.size(); ++i) {
        if (resources[i] > 0) {
            text.setString(resourceNames[i] + ":" + std::to_string(resources[i]));
            text.setPosition(xOffset, yOffset + i * yStep);
            window.draw(text);
        }
    }

    int numPlayers = players.size();
    if (numPlayers > 0) {
        sf::Text playerCountText;
        playerCountText.setFont(font);
        playerCountText.setCharacterSize(12);
        playerCountText.setFillColor(sf::Color::Black);
        playerCountText.setString(std::to_string(numPlayers));
        playerCountText.setPosition(shape.getPosition().x + shape.getSize().x - 13, shape.getPosition().y + shape.getSize().y - 13);
        window.draw(playerCountText);
    }

    for (const auto &player : players) {
        player->textInfo.setFont(font);
        player->textInfo.setCharacterSize(20);
        player->textInfo.setFillColor(sf::Color::White);
        player->textInfo.setPosition(sf::Vector2f(window.getSize().x - 350, 24 * player->getId()));
        player->textInfo.setString("id:" + std::to_string(player->getId()) + " T:" + 
                        player->getTeamName() + " lvl:" + 
                        std::to_string(player->getLevel()) + " : " + 
                        player->getResource(0) + ", " + 
                        player->getResource(1) + ", " + 
                        player->getResource(2) + ", " + 
                        player->getResource(3) + ", " + 
                        player->getResource(4) + ", " + 
                        player->getResource(5) + ", " + 
                        player->getResource(6));
        window.draw(player->textInfo);
    }

    for (const auto &player : players) {
        sf::CircleShape playerShape(10);
        playerShape.setFillColor(sf::Color::Blue);
        playerShape.setPosition(shape.getPosition().x + (shape.getSize().x / 2) - playerShape.getRadius(),
                                shape.getPosition().y + (shape.getSize().y / 2) - playerShape.getRadius());

        player->setPosition(shape.getPosition().x + (shape.getSize().x / 2) - playerShape.getRadius(),
                                shape.getPosition().y + (shape.getSize().y / 2) - playerShape.getRadius());
        window.draw(playerShape);

        sf::CircleShape orientationShape(3);
        orientationShape.setFillColor(sf::Color::Yellow);

        float offset = 12;
        float centerX = shape.getPosition().x + (shape.getSize().x / 2);
        float centerY = shape.getPosition().y + (shape.getSize().y / 2);

        switch (player->getOrientation()) {
            case 3:
                orientationShape.setPosition(centerX - orientationShape.getRadius(), centerY - offset - orientationShape.getRadius());
                break;
            case 2:
                orientationShape.setPosition(centerX + offset - orientationShape.getRadius(), centerY - orientationShape.getRadius());
                break;
            case 1:
                orientationShape.setPosition(centerX - orientationShape.getRadius(), centerY + offset - orientationShape.getRadius());
                break;
            case 4:
                orientationShape.setPosition(centerX - offset - orientationShape.getRadius(), centerY - orientationShape.getRadius());
                break;
            default:
                break;
        }
        
        window.draw(orientationShape);
    }

    for (const auto &player : players) {
        player->textInfo.setFont(font);
        player->textInfo.setCharacterSize(20);
        player->textInfo.setFillColor(sf::Color::White);
        player->textInfo.setPosition(sf::Vector2f(window.getSize().x - 350, 24 * player->getId()));
        player->textInfo.setString("id:" + std::to_string(player->getId()) + " T:" + 
                        player->getTeamName() + " lvl:" + 
                        std::to_string(player->getLevel()) + " : " + 
                        player->getResource(0) + ", " + 
                        player->getResource(1) + ", " + 
                        player->getResource(2) + ", " + 
                        player->getResource(3) + ", " + 
                        player->getResource(4) + ", " + 
                        player->getResource(5) + ", " + 
                        player->getResource(6));
        window.draw(player->textInfo);
    }
    for (const auto &player : players) {
        player->textMove.setFont(font);
        player->textMove.setPosition(1100, 24 * player->getId());
        player->textMove.setCharacterSize(16);
        player->textMove.setFillColor(sf::Color::White);
        startY += 20;
        player->textMove.setString("Player " + std::to_string(player->getId()) +
                        " move to (" + std::to_string(player->xTile) + ", " +
                        std::to_string(player->yTile) + "), orientation: " +
                        std::to_string(player->getOrientation()));
        window.draw(player->textMove);
    }

    for (long unsigned int i = 0; i < eggs.size(); ++i) {
        sf::CircleShape egg(5);
        egg.setFillColor(sf::Color::Red);
        egg.setPosition(shape.getPosition().x + (shape.getSize().x / 2) - egg.getRadius(),
                        shape.getPosition().y + (shape.getSize().y / 2) - egg.getRadius());
        window.draw(egg);
    }

    for (const auto &player : players) {
        sf::RectangleShape IncantShape(sf::Vector2f(20.0, 20.0));
        IncantShape.setOutlineThickness(3);
        IncantShape.setOrigin(sf::Vector2f(10.0, 10.0));
        IncantShape.setFillColor(sf::Color::Transparent);
        IncantShape.setPosition(shape.getPosition().x + (shape.getSize().x / 2), shape.getPosition().y + (shape.getSize().y / 2));
        if (player->getIncant() == true) {
            IncantShape.setOutlineColor(sf::Color::Magenta);
        } else {
            IncantShape.setOutlineColor(sf::Color::Transparent);
        }
            
        window.draw(IncantShape);
    }
}

std::array<int, 7> Tile::getResources() const {
    return resources;
}
