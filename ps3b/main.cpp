// Copyright 2025 Peter Meas
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " T dt < universe_file\n";
        return 1;
    }
    bool fontLoad = false;

    double T = std::stod(argv[1]);     // Total simulation time
    double dt = std::stod(argv[2]);    // Time step

        sf::RenderWindow window(sf::VideoMode(800, 600), "N-Body Simulation");
        window.setFramerateLimit(60);
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Couldn't load font" << std::endl;
    } else {
        fontLoad = true;
    }

    sf::Text timetext;
    if (fontLoad) {
    timetext.setFont(font);
    timetext.setCharacterSize(20);
    timetext.setFillColor(sf::Color::White);
    timetext.setPosition(10, 10);
    }

    sf::RectangleShape timerBackground(sf::Vector2f(200, 30));
    timerBackground.setFillColor(sf::Color(0, 0, 0, 128));
    timerBackground.setPosition(10, 10);

    NB::Universe universe(window.getSize());
    try {
        universe.loadFromStream(std::cin);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }



    double elapsed_time = 0.0;
    sf::Clock clock;

    while (window.isOpen() && elapsed_time < T) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        universe.step(dt);
        elapsed_time += dt;

        std::ostringstream timeStr;
        double days = elapsed_time / 86400.0;
        timeStr << "Elasped time" << std::fixed << std::setprecision(2) << days << "days";


        if (fontLoad) {
            timetext.setString(timeStr.str());
        }

        window.clear();
        window.draw(universe);

        if (fontLoad) {
            window.draw(timerBackground);
            window.draw(timetext);
        } else {
            window.draw(timerBackground);
            sf::RectangleShape bar(sf::Vector2f((elapsed_time / T) * 180, 10));
            bar.setFillColor(sf::Color::Yellow);
            bar.setPosition(20, 20);
            window.draw(bar);
        }
        window.display();
    }
    std::cout << universe;
    return 0;
}
