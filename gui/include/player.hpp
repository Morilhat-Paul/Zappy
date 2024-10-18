/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** player.hpp
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <array>
#include <iostream>
#include <string>
#include <sstream>

class Player {
public:
    Player(int id, int x, int y, int orientation, int level, const std::string& teamName)
        : id(id), x(x), y(y), orientation(orientation), level(level), teamName(teamName), doBeBroadcasting(false) {}

    int getId();
    int getX();
    int getY();
    int xTile;
    int yTile;
    int getOrientation() const;
    void setResource(long unsigned int resource, int quantity);
    std::string getResource(int val);
    int getLevel();
    void setBroadcast(bool value);
    bool getBroadcast() const;
    void setIncant(bool value);
    bool getIncant() const;
    const std::string& getTeamName();

    void setPosition(int newX, int newY);
    void setOrientation(int newOrientation);
    void setLevel(int newLevel);
    sf::Clock c;
    sf::Time t;
    sf::Text textInfo;
    sf::Text textMove;

private:
    int id;
    int x;
    int y;
    int orientation;
    int level;
    std::string teamName;
    std::array<int, 7> resources;
    bool doBeBroadcasting;
    bool doBeIncant;
};
#endif // PLAYER_HPP
