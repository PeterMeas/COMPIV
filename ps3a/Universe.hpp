// Copyright 2025 Peter Meas
#pragma once
#include <iostream>
#include <memory>
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

namespace NB {
class Universe : public sf::Drawable {
 public:
    explicit Universe();  // Required
    explicit Universe(const sf::Vector2u& windowSize);
    void loadFromStream(std::istream& is);

    explicit Universe(const std::string& filename);  // Optional

    size_t size() const;  // Optional num of bodies
    double radius() const;  // Optional universe radius

    const CelestialBody& operator[](size_t i) const;  // Optional

    void step(double dt);  // Implemented in part b, behavior for part a is undefined
    friend std::istream& operator>>(std::istream& is, Universe& uni);
    friend std::ostream& operator<<(std::ostream& os, const Universe& uni);

 protected:
    void draw(sf::RenderTarget& window,
    sf::RenderStates states) const override;  // From sf::Drawable

 private:
      size_t numBodies;  // number of bodies
      double universeRadius;
      sf::Vector2u windowSize;
      //  vector of shared pointers to celestial bodies
      std::vector<std::shared_ptr<CelestialBody>> bodies;
    // Fields and helper functions go here
};

}  // namespace NB
