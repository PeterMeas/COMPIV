// Copyright 2025 Peter Meas
#pragma once
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>


class Triangle : public sf::Drawable{
 public:
    //  Triangle(double sideLength = 0, sf::Vector2f centroidPos = sf::Vector2f(0,0));
    Triangle(double sideLength, sf::Vector2f centroidPos);
    void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
    void fractal(sf::RenderTarget& target, int n);
    sf::Color getDepthColor(int depth);
 private:
    double height;
    double L;
    sf::Vector2f centroid;
    sf::ConvexShape shape;

    void drawTriangle(sf::RenderWindow& window, sf::Vector2f pos,
    double size, int depth, float rotation);
};
