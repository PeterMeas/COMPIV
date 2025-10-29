// Copyright 2025 Peter Meas
#pragma once

#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

namespace NB {
class CelestialBody: public sf::Drawable {
 public:
    explicit CelestialBody();  // Required
    CelestialBody(double x, double y, double vx, double vy,
    float mass, const std::string& imageFilename, double universeRadius,
    const sf::Vector2u& windowSize);
    friend std::istream& operator>>(std::istream& is, CelestialBody& uni);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& uni);


      void setPosition(double newX, double newY);
      void setVelocity(double newVX, double newVY);
      std::string imageFilename() const;
      void setUniverseRadius(double radius);
    sf::Vector2f position() const;  //  Optional
    sf::Vector2f velocity() const;  //  Optional
    float mass() const;  //  Optional

 protected:
    void draw(sf::RenderTarget& window,
    sf::RenderStates states) const override;  // From sf::Drawable

 private:
      double x, y;  // pos
      double vx, vy;  // velocity
      double _mass;  // mass
      std::string _imageFilename;  // filename for the image
      std::shared_ptr<sf::Texture> texture;  // texture for the image
      mutable sf::Sprite sprite;  // sprite for the image
      double universeRadius;
      sf::Vector2u windowSize;
    // Fields and helper methods go here
};
}  // namespace NB
