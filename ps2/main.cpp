// Copyright 2025 Peter Meas
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include "triangle.hpp"
#include <SFML/Graphics.hpp>

int main(int argc, char** argv) {
    if (argc != 3) {
        std::cerr << "Invalid arguments!" << std::endl;
    } else {
        double L = std::stod(argv[1]);
        int N = std::stoi(argv[2]);
        int windowSize = static_cast<int>(2 * std::sqrt(3.0) * L);
        // Create window with calculated dimensions
        sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Sierpinski Triangle");
        // Center the triangle in the window
        Triangle triangle(L, sf::Vector2f(windowSize / 2, windowSize / 2));

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            window.clear(sf::Color::White);
            triangle.fractal(window, N);
            window.display();
        }
    }
    return 0;
}
