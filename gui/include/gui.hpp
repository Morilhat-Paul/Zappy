/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** gui.hpp
*/

#ifndef GUI_HPP
#define GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "tile.hpp"
#include "network.hpp"
#include <memory>

class GUI {
public:
    GUI(Network& network);
    void run();

private:
    void processEvents();
    void update();
    void render();
    Tile* getTileAt(int x, int y);

    void handleWelcome(const std::string& message);
    void handleMsz(const std::string& message);
    void handleBct(const std::string& message);
    void handlePpo(const std::string& message);
    void handleEnw(const std::string& message);
    void handlePfk(const std::string& message);
    void handleTna(const std::string& message);
    void handleKo(const std::string& message);
    void handlePnw(const std::string& message);
    void handlePin(const std::string& message);
    void handleEbo(const std::string& message);
    void handlePlv(const std::string& message);
    void handlePdi(const std::string& message);
    void handlePbc(const std::string& message);
    void handlePic(const std::string& message);
    void handlePie(const std::string& message);
    void createTiles();
    void processMessage(const std::string &message);
    std::shared_ptr<Player> getPlayerById(int id);
    void requestPlayerPositions();

    sf::RenderWindow window;
    Network& network;
    std::vector<Tile> tiles;
    int mapWidth;
    int mapHeight;
    float tileSize;
    sf::Font font;
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::string> actions;
    std::vector<std::string> info;
    sf::Text infoText;
};

#endif // GUI_HPP
