// Copyright 2025 Peter Meas
#include <iostream>
#include <fstream>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " T dt < universe_file\n";
        return 1;
    }

    double T = std::stod(argv[1]);     // Total simulation time
    double dt = std::stod(argv[2]);    // Time step

        sf::RenderWindow window(sf::VideoMode(800, 600), "N-Body Simulation");
        window.setFramerateLimit(60);
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

        window.clear();
        window.draw(universe);
        window.display();
    }
    std::cout << universe;

    return 0;
}
