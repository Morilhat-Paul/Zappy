/*
** EPITECH PROJECT, 2023
** Untitled (Workspace)
** File description:
** menu.cpp
*/

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

bool showMenu(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("gui/ressources/Playground.ttf")) {
        std::cerr << "Error loading font\n";
        return false;
    }

    // 2D pour le Ciel
    sf::Texture texture;
    if (!texture.loadFromFile("gui/ressources/menu.jpg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::Text zappy;
    zappy.setFont(font);
    zappy.setString("Zappy");
    zappy.setCharacterSize(200);
    zappy.setFillColor(sf::Color::Black);
    zappy.setStyle(sf::Text::Bold);
    zappy.setOutlineThickness(2.5f);
    zappy.setOutlineColor(sf::Color::White);
    zappy.setPosition(
        window.getSize().x / 2.0f - zappy.getGlobalBounds().width / 2.0f,
        window.getSize().y / 3.0f - zappy.getGlobalBounds().height / 2.0f
    );

    sf::Text startButton;
    startButton.setFont(font);
    startButton.setString("start");
    startButton.setCharacterSize(100);
    startButton.setFillColor(sf::Color::White);
    startButton.setStyle(sf::Text::Bold);
    startButton.setOutlineThickness(2.5f);
    startButton.setOutlineColor(sf::Color::Black);
    startButton.setPosition(
        window.getSize().x / 2.0f - startButton.getGlobalBounds().width / 2.0f,
        window.getSize().y / 1.7f - startButton.getGlobalBounds().height / 2.0f
    );

    sf::Text creator;
    creator.setFont(font);
    creator.setString("Loic OSTERNAUD, Paul MORILLAT, Camille ERADES, Clement MONNOIR, Malo COET, Quentin CHARILLON");
    creator.setCharacterSize(25);
    creator.setFillColor(sf::Color::White);
    creator.setStyle(sf::Text::Bold);
    creator.setPosition(
        window.getSize().x / 2.0f - creator.getGlobalBounds().width / 2.0f,
        window.getSize().y / 1.1f - creator.getGlobalBounds().height / 2.0f
    );

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        return true;  // Start the game
                    }
                }
            }
        }

        window.clear();
        window.draw(sprite);
        window.draw(startButton);
        window.draw(zappy);
        window.draw(creator);
        window.display();
    }
    return false;
}