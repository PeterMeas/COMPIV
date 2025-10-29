//  Copyright 2025 Peter Meas //
#include <iostream>
#include <string>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


int main(int argc, char** argv) {
    char* input_file = argv[1];
    char* output_file = argv[2];
    char* arg3 = argv[3];
    if (argc != 4) {
        std::cout << "Invalid Arguemnts!" << std::endl
        << "argv[1] input-file.png" << std::endl
        << "argv[2] output-file.png" << std::endl
        << "argv[3] FibLFSR seed" << std::endl;
        return -1;
    }
    sf::Image image;
    if (!image.loadFromFile(input_file))
    return -1;
    //  p is a pixelimage.getPixel(x, y);

    PhotoMagic::FibLFSR seed(arg3);
    PhotoMagic::transform(image, &seed);

    //  sf::Color p;

    sf::Vector2u size = image.getSize();
    sf::RenderWindow Original(sf::VideoMode(size.x, size.y), "Original");
    sf::RenderWindow Transformed(sf::VideoMode(size.x, size.y), "Transformed");

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Image w2;
    w2.loadFromFile(input_file);

    sf::Texture texture2;
    texture2.loadFromImage(w2);

    sf::Sprite sprite2;
    sprite2.setTexture(texture2);

    while (Original.isOpen() && Transformed.isOpen()) {
        sf::Event event;
        while (Original.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            Original.close();
            }
            while (Transformed.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
                Transformed.close();
    }
        Original.clear(sf::Color::White);
        Original.draw(sprite2);
        Original.display();
        Transformed.clear(sf::Color::White);
        Transformed.draw(sprite);
        Transformed.display();
        }

        std::cout << "Input file: " << input_file << std::endl;
        std::cout << "Output file: " << output_file << std::endl;
        sf::Image input;
        input.loadFromFile(input_file);

    //  fredm: saving a PNG segfaults for me, though it does properly
    //  write the file
    if (!image.saveToFile(output_file))
        return -1;
    return 0;
}
