/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gui.cpp
*/

#include "../include/gui.hpp"
#include "../include/tile.hpp"
#include <iostream>
#include <sstream>
#include "menu.hpp"

GUI::GUI(Network& network) 
    : window(sf::VideoMode(1920, 1080), "SFML GUI"), network(network), mapWidth(0), mapHeight(0), tileSize(0.0f) {
    network.registerHandler("WELCOME", [this](const std::string& msg) { handleWelcome(msg); });
    network.registerHandler("msz", [this](const std::string& msg) { handleMsz(msg); });
    network.registerHandler("bct", [this](const std::string& msg) { handleBct(msg); });
    network.registerHandler("tna", [this](const std::string& msg) { handleTna(msg); });
    network.registerHandler("ppo", [this](const std::string& msg) { handlePpo(msg); });
    network.registerHandler("pin", [this](const std::string& msg) { handlePin(msg); });
    network.registerHandler("enw", [this](const std::string& msg) { handleEnw(msg); });
    network.registerHandler("pfk", [this](const std::string& msg) { handlePfk(msg); });
    network.registerHandler("plv", [this](const std::string& msg) { handlePlv(msg); });
    network.registerHandler("pdi", [this](const std::string& msg) { handlePdi(msg); });
    network.registerHandler("pbc", [this](const std::string& msg) { handlePbc(msg); });
    network.registerHandler("pic", [this](const std::string& msg) { handlePic(msg); });
    network.registerHandler("pie", [this](const std::string& msg) { handlePie(msg); });
    network.registerHandler("ko", [this](const std::string& msg) { handleKo(msg); });

    if (!font.loadFromFile("gui/ressources/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
    }
}

void GUI::run() {
    if (!showMenu(window))
        return;
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void GUI::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            std::cout << "Window close event received" << std::endl;
            window.close();
        }// else if (event.type == sf::Event::KeyPressed) {
        //     if (event.key.code == sf::Keyboard::I) {
        //         std::cout << "I key pressed, requesting player positions" << std::endl;
        //         requestPlayerPositions();
        //     }
        // }
    }
}

void GUI::update() {
    std::queue<std::string> messages;
    network.receiveMessages(messages);
    while (!messages.empty()) {
        processMessage(messages.front());
        messages.pop();
    }
}

void GUI::render() {

    for (const auto& tile : tiles) {
        tile.draw(window, font);
    }
    for (const auto& player : players) {
        sf::CircleShape BroadcastShape(20);
        BroadcastShape.setOutlineThickness(5);
        BroadcastShape.setOrigin(sf::Vector2f(10.0, 10.0));
        BroadcastShape.setFillColor(sf::Color::Transparent);
        BroadcastShape.setPosition(player->getX(), player->getY());
        if (player->getBroadcast() == true) {
            BroadcastShape.setOutlineColor(sf::Color::Yellow);
        } else {
            BroadcastShape.setOutlineColor(sf::Color::Transparent);
        }
        player->t = player->c.getElapsedTime();
        if (player->t.asSeconds() >= 0.1)
            player->setBroadcast(false);
            
        window.draw(BroadcastShape);
    }
    window.display();
    window.clear(sf::Color::Black);
}

Tile* GUI::getTileAt(int x, int y) {
    int tileX = x / tileSize;
    int tileY = y / tileSize;
    int index = tileY * mapWidth + tileX;
    if (index >= 0 && static_cast<size_t>(index) < tiles.size()) {
        return &tiles[index];
    }
    return nullptr;
}

void GUI::handleWelcome(const std::string& message) {
    std::cout << "Received WELCOME message from server." << std::endl;
    network.sendMessage("GRAPHIC\n");
}

void GUI::handleMsz(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    stream >> type >> mapWidth >> mapHeight;
    std::cout << "Map size: " << mapWidth << "x" << mapHeight << std::endl;

    createTiles();
}

void GUI::handleBct(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    int x, y, q0, q1, q2, q3, q4, q5, q6;
    stream >> type >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;

    int index = y * mapWidth + x;
    if (index >= 0 && static_cast<size_t>(index) < tiles.size()) {
        tiles[index].setResource(0, q0);
        tiles[index].setResource(1, q1);
        tiles[index].setResource(2, q2);
        tiles[index].setResource(3, q3);
        tiles[index].setResource(4, q4);
        tiles[index].setResource(5, q5);
        tiles[index].setResource(6, q6);
    }
}

void GUI::handlePpo(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    int playerId, x, y, orientation;
    stream >> type >> playerId >> x >> y >> orientation;

    std::cout << "Handling ppo message: playerId=" << playerId << ", x=" << x << ", y=" << y << ", orientation=" << orientation << std::endl;

    for (auto& tile : tiles) {
        tile.removePlayer(playerId);
    }

    int index = y * mapWidth + x;
    if (index >= 0 && static_cast<size_t>(index) < tiles.size()) {
        //int level = 1;
        //std::string teamName = "default";
        
        //Player player(playerId, x, y, orientation, level, teamName);
        getPlayerById(playerId)->setOrientation(orientation);
        getPlayerById(playerId)->setPosition(x, y);
        getPlayerById(playerId)->xTile = x;
        getPlayerById(playerId)->yTile = y;
        tiles[index].addPlayer(getPlayerById(playerId));
        std::cout << "Player " << playerId << " added to tile at index " << index << std::endl;
    } else {
        std::cout << "Invalid tile index for player position update: " << index << std::endl;
    }
}

void GUI::handleEnw(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    int eggId, playerId, x, y;
    stream >> type >> eggId >> playerId >> x >> y;

    std::cout << "Egg " << eggId << " laid by player " << playerId << " at (" << x << ", " << y << ")" << std::endl;

    int index = y * mapWidth + x;
    if (index >= 0 && static_cast<size_t>(index) < tiles.size()) {
        tiles[index].addEgg(eggId);
        std::cout << "Egg " << eggId << " added to tile (" << x << ", " << y << ")" << std::endl;
    } else {
        std::cout << "Index out of bounds for egg position update: " << index << std::endl;
    }
}

void GUI::handlePfk(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    int playerId;
    stream >> type >> playerId;

    std::cout << "Player " << playerId << " has laid an egg." << std::endl;
}

void GUI::handlePnw(const std::string& message) {
    std::istringstream stream(message);
    std::string type, teamName;
    int playerId, x, y, orientation, level;
    stream >> type >> playerId >> x >> y >> orientation >> level >> teamName;

    std::cout << "Handling pnw message: playerId=" << playerId << ", x=" << x << ", y=" << y << ", orientation=" << orientation << ", level=" << level << ", teamName=" << teamName << std::endl;

    players.push_back(std::make_shared<Player>(Player(playerId, x, y, orientation, level, teamName)));

    int index = y * mapWidth + x;
    if (index >= 0 && static_cast<size_t>(index) < tiles.size()) {
        tiles[index].addPlayer(players.back());
        std::cout << "New player " << playerId << " added to tile at index " << index << std::endl;
    } else {
        std::cout << "Invalid tile index for new player: " << index << std::endl;
    }
}

void GUI::handlePin(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    int playerId, x, y, q0, q1, q2, q3, q4, q5, q6;
    stream >> type >> playerId >> x >> y >> q0 >> q1 >> q2 >> q3 >> q4 >> q5 >> q6;
    std::cout << "Received 'pin' from server, indicating the inventory of requested player " << playerId << std::endl;
    for (auto& player : players) {
        if (player->getId() == playerId) {
            player->setResource(0, q0);
            player->setResource(1, q1);
            player->setResource(2, q2);
            player->setResource(3, q3);
            player->setResource(4, q4);
            player->setResource(5, q5);
            player->setResource(6, q6);
            return;
        }
    }
}

std::shared_ptr<Player> GUI::getPlayerById(int id)
{
    for (auto& player : players) {
        if (player->getId() == id) {
            return player;
        }
    }
    return nullptr;
}

void GUI::handleTna(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    std::string team;
    stream >> type >> team;

    std::cout << "Teams " << team <<  std::endl;
}

void GUI::handleEbo(const std::string& message)
{
    std::istringstream stream(message);
    std::string type;
    int eggId;
    stream >> type >> eggId;

    for (auto& tile : tiles) {
        tile.removeEgg(eggId);
    }
}

void GUI::handlePdi(const std::string& message)
{
    std::istringstream stream(message);
    std::string type;
    int playerId;
    stream >> type >> playerId;

    for (auto& tile : tiles) {
        tile.removePlayer(playerId);
    }
}

void GUI::handlePlv(const std::string& message)
{
    std::istringstream stream(message);
    std::string type;
    int playerId, level;
    stream >> type >> playerId >> level;

    std::cout << "Handling plv message: playerId=" << playerId << ", level=" << level << std::endl;

    for (auto& player : players) {
        if (player->getId() == playerId) {
            player->setLevel(level);
            std::cout << "Player " << playerId << " level set to " << level << std::endl;
            return;
        }
    }
    std::cerr << "Player with ID " << playerId << " not found for level update." << std::endl;
}

void GUI::handlePbc(const std::string& message)
{
    std::istringstream stream(message);
    std::string type;
    int playerId, m;
    stream >> type >> playerId >> m;
    for (auto& player : players) {
        if (player->getId() == playerId) {
            player->setBroadcast(true);
            player->c.restart();
            return;
        }
    }
}

void GUI::handlePic(const std::string& message)
{
    std::istringstream stream(message);
    std::string type;
    int playerId, m;
    stream >> type >> playerId >> m;
    for (auto& player : players) {
        if (player->getId() == playerId) {
            player->setIncant(true);
            return;
        }
    }
}

void GUI::handlePie(const std::string& message)
{
    std::istringstream stream(message);
    std::string type;
    int playerId, m;
    stream >> type >> playerId >> m;
    for (auto& player : players) {
        if (player->getId() == playerId) {
            player->setIncant(false);
            return;
        }
    }
}

void GUI::handleKo(const std::string& message) {
    std::cout << "Received 'ko' from server, indicating an error or unrecognized command." << std::endl;
}

void GUI::createTiles() {
    tiles.clear();
    tileSize = std::min(window.getSize().x / static_cast<float>(mapWidth), window.getSize().y / static_cast<float>(mapHeight));
    
    std::cout << "Creating tiles of size: " << tileSize << std::endl;

    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            tiles.emplace_back(tileSize, x, y);
        }
    }

    std::cout << "Total tiles created: " << tiles.size() << std::endl;
}

void GUI::processMessage(const std::string& message) {
    std::istringstream stream(message);
    std::string type;
    stream >> type;

    if (type == "WELCOME") {
        handleWelcome(message);
    } else if (type == "msz") {
        handleMsz(message);
    } else if (type == "pnw") {
        handlePnw(message);
    } else if (type == "bct") {
        handleBct(message);
    } else if (type == "ppo") {
        handlePpo(message);
    } else if (type == "pin") {
        handlePin(message);
    } else if (type == "pfk") {
        handlePfk(message);
    } else if (type == "tna") {
        handleTna(message);
    } else if (type == "enw") {
        handleEnw(message);
    } else if (type == "ebo") {
        handleEbo(message);
    } else if (type == "plv") {
        handlePlv(message);
    } else if (type == "pdi") {
        handlePdi(message);
    } else if (type == "pbc") {
        handlePbc(message);
    } else if (type == "pic") {
        handlePic(message);
    } else if (type == "pie") {
        handlePie(message);
    } else if (type == "ko") {
        handleKo(message);
    }
}

void GUI::requestPlayerPositions()
{
    // network.sendMessage("mct\n");
    // for (auto &player : players) {
    //     std::stringstream ppoMessage;
    //     ppoMessage << "ppo #" << player.getId() << "\n";
    //     network.sendMessage(ppoMessage.str());

    //     std::stringstream plvMessage;
    //     plvMessage << "plv #" << player.getId() << "\n";
    //     network.sendMessage(plvMessage.str());
    // }
}
