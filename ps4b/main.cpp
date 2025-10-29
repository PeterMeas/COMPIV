// Copyright 2025 Peter Meas
#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>" << std::endl;
        return 1;
    }

    //  Sokoban instance
    SB::Sokoban sokoban;
    // load lkevel
    std::ifstream levelFile(argv[1]);
    if (!levelFile) {
        std::cerr << "Error: Could not open file " << argv[1] << std::endl;
        return 1;
    }
    // Read the level data
    levelFile >> sokoban;
    levelFile.close();

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Warning: couldnt load font" << std::endl;
    }

    sf::RenderWindow window(
        sf::VideoMode(sokoban.pixelWidth(), sokoban.pixelHeight()), "Sokoban");

    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (sokoban.isWon() && event.key.code != sf::Keyboard::R &&
                event.key.code != sf::Keyboard::Escape) {
                    continue;
                }
                switch (event.key.code) {
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                        sokoban.movePlayer(SB::Direction::Up);
                        break;
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                        sokoban.movePlayer(SB::Direction::Down);
                        break;
                    case sf::Keyboard::A:
                    case sf::Keyboard::Left:
                        sokoban.movePlayer(SB::Direction::Left);
                        break;
                    case sf::Keyboard::D:
                    case sf::Keyboard::Right:
                        sokoban.movePlayer(SB::Direction::Right);
                        break;
                    case sf::Keyboard::R:
                        sokoban.reset();
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default:
                        break;
                }
            }
        }
        window.clear();
        window.draw(sokoban);
        window.display();
    }
    return 0;
}
