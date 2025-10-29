// Copyright 2025 Peter Meas
#include "CelestialBody.hpp"
#include <string>
#include <stdexcept>

namespace NB {

CelestialBody::CelestialBody()
: x(0), y(0), vx(0), vy(0), _mass(0.0), _imageFilename(""), universeRadius(0), windowSize(0, 0) {
    texture = std::make_shared<sf::Texture>();
    sprite.setTexture(*texture);
}

CelestialBody::CelestialBody(double x, double y, double vx,
double vy, float mass, const std::string& imageFilename,
double universeRadius, const sf::Vector2u& windowSize)
: x(x), y(y), vx(vx), vy(vy), _mass(mass),
_imageFilename(imageFilename),
universeRadius(universeRadius), windowSize(windowSize) {
    // Load texture
    texture = std::make_shared<sf::Texture>();
    if (!texture->loadFromFile(_imageFilename)) {
        throw std::runtime_error("Failed to load image: " + _imageFilename);
    }

    // Set sprite texture
    sprite.setTexture(*texture);

    // Calculate scaled screen positions
    float scaleX = static_cast<float>(windowSize.x) / (2 * universeRadius);
    float scaleY = static_cast<float>(windowSize.y) / (2 * universeRadius);

    float screenX = x * scaleX + windowSize.x / 2;
    float screenY = -y * scaleY + windowSize.y / 2;  // Invert Y-axis

    // Set sprite position
    sprite.setPosition(screenX, screenY);
}

std::string CelestialBody::imageFilename() const {
    return _imageFilename;
}

sf::Vector2f CelestialBody::position() const {
    return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
}
sf::Vector2f CelestialBody::velocity() const {
    return sf::Vector2f(static_cast<float>(vx), static_cast<float>(vy));
}

float CelestialBody::mass() const {
    return static_cast<float>(_mass);
}

void CelestialBody::setUniverseRadius(double radius) {
    this->universeRadius = radius;
    float scaleX = static_cast<float>(windowSize.x) / (2 * universeRadius);
    float scaleY = static_cast<float>(windowSize.y) / (2 * universeRadius);

    float screenX = x * scaleX + windowSize.x / 2;
    float screenY = -y * scaleY + windowSize.y / 2;  // Invert Y-axis

    sprite.setPosition(screenX, screenY);
}

void CelestialBody::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(sprite, states);
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    double x, y, vx, vy, mass;
    std::string filename;

    if (!(is >> x >> y >> vx >> vy >> mass >> filename)) {
        throw std::runtime_error("Failed to read celestial body data");
    }

    if (mass < 0) {
        throw std::runtime_error("Negative mass");
    }

    // Assign values to the body
    body.x = x;
    body.y = y;
    body.vx = vx;
    body.vy = vy;
    body._mass = mass;
    body._imageFilename = filename;

    if (body._imageFilename.empty()) {
        throw std::runtime_error("Image filename is missing");
    }
    if (!body.texture->loadFromFile(body._imageFilename)) {
        throw std::runtime_error("Failed to load image: " + body._imageFilename);
    }
    body.sprite.setTexture(*body.texture);
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& uni) {
    os << uni.x << " " << uni.y << " "
    << uni.vx << " " << uni.vy << " "
    << uni._mass << " " << uni._imageFilename;
    return os;
}

void CelestialBody::setPosition(double newX, double newY) {
    x = newX;
    y = newY;

    // . update sprite position
    float scaleX = static_cast<float>(windowSize.x) / (2 * universeRadius);
    float scaleY = static_cast<float>(windowSize.y) / (2 * universeRadius);

    float screenX = x * scaleX + windowSize.x / 2;
    float screenY = -y * scaleY + windowSize.y / 2;

    sprite.setPosition(screenX, screenY);
}

void CelestialBody::setVelocity(double newVX, double newVY) {
    vx = newVX;
    vy = newVY;
}
}  //  namespace NB
