// Copyright 2025 Mohamed Bouchtout and Peter Meas

#include <iostream>
#include <string>
#include <fstream>
#include <SFML/System.hpp>
#include "EDistance.hpp"

int main() {
    std::string s1;
    std::string s2;

    if (!std::getline(std::cin, s1)) {
        std::cerr << "Error: Failed to read first line!\n";
        exit(1);
    }

    if (!std::getline(std::cin, s2)) {
        std::cerr << "Error: Failed to read second line!\n";
        exit(1);
    }

    sf::Clock clock;

    EDistance ed(s1, s2);
    ed.optDistance();

    sf::Time t = clock.getElapsedTime();
    std::cout << "Edit distance = " << ed.optDistance() << std::endl;
    std::cout << ed.alignment() << std::endl;
    std::cout << "Execution time is " << t.asSeconds()
                         << " seconds" << std::endl;

    return 0;
}