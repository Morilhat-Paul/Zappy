/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** player.cpp
*/

#include "../include/player.hpp"

int Player::getId()
{
    return id;
}

int Player::getX()
{
    return x;
}

int Player::getY()
{
    return y;
}

int Player::getOrientation() const
{
    return orientation;
}

int Player::getLevel()
{
    return level;
}

std::string Player::getResource(int val)
{
    return std::to_string(resources[val]);
}

const std::string& Player::getTeamName()
{
    return teamName;
}

void Player::setPosition(int newX, int newY)
{
    x = newX;
    y = newY;
}

void Player::setOrientation(int newOrientation)
{
    orientation = newOrientation;
}

void Player::setLevel(int newLevel)
{
    level = newLevel;
}

void Player::setResource(long unsigned int resource, int quantity) {
    if (resource >= 0 && resource < resources.size()) {
        resources[resource] = quantity;
    }
}

void Player::setBroadcast(bool value)
{
    doBeBroadcasting = value;
}

bool Player::getBroadcast() const
{
    return doBeBroadcasting;
}

void Player::setIncant(bool value)
{
    doBeIncant = value;
}

bool Player::getIncant() const
{
    return doBeIncant;
}
