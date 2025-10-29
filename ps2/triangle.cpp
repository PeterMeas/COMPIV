// Copyright 2025 Peter Meas
#include "triangle.hpp"

Triangle::Triangle(double sideLength, sf::Vector2f centroidPos)
    : L(sideLength), centroid(centroidPos) {
    height = static_cast<float>((sqrt(3) / 2) * L);
    shape.setPointCount(3);
    shape.setPoint(0, sf::Vector2f(0, height / 2));  // BOTTOM VERTEX
    shape.setPoint(1, sf::Vector2f(-L / 2, -height / 2));  // TOP LEFT
    shape.setPoint(2, sf::Vector2f(L / 2, -height / 2));  // TOP RIGHT
   shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(.2f);
    shape.setPosition(centroid);
}


sf::Color Triangle::getDepthColor(int depth) {
    // Use modulo to cycle through colors
    switch (depth % 6) {
        case 0:
            return sf::Color(148, 0, 211);    // Purple
        case 1:
            return sf::Color(75, 0, 130);     // Indigo
        case 2:
            return sf::Color(0, 0, 255);      // Blue
        case 3:
            return sf::Color(0, 255, 0);      // Green
        case 4:
            return sf::Color(255, 255, 0);    // Yellow
        case 5:
            return sf::Color(255, 127, 0);    // Orange
        default:
            return sf::Color(255, 0, 0);      // Red
    }
}

void Triangle::draw(sf::RenderTarget& target, sf::RenderStates state)const {
     target.draw(shape, state);
}

void Triangle::fractal(sf::RenderTarget& target, int n) {
    if (n < 0) return;
    shape.setFillColor(getDepthColor(n));
    target.draw(*this);
    double newSideLength = L/2;
    double height = (sqrt(3) / 2) * L;

    // Calculate positions for the three outer triangles
    sf::Vector2f bottom(
        centroid.x - L/4,
        centroid.y + height/1.33
);

    sf::Vector2f left(
        centroid.x - L/1.99,
        centroid.y - height/1.33
);

    sf::Vector2f right(
        centroid.x + L/1.33,
        centroid.y - height/4
);
    // Recursively draw the three outer triangles
    Triangle bottomTriangle(newSideLength, bottom);
    Triangle leftTriangle(newSideLength, left);
    Triangle rightTriangle(newSideLength, right);

    bottomTriangle.fractal(target, n-1);
    leftTriangle.fractal(target, n-1);
    rightTriangle.fractal(target, n-1);
}
