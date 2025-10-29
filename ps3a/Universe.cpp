// Copyright 2025 Peter Meas
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <memory>
#include "Universe.hpp"
#include "CelestialBody.hpp"

namespace NB {

Universe::Universe(const sf::Vector2u& windowSize) : windowSize(windowSize) {}

Universe::Universe() : numBodies(0), universeRadius(0) {}

Universe::Universe(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    inputFile >> *this;
}

void Universe::loadFromStream(std::istream& is) {
    if (!(is >> numBodies >> universeRadius)) {
        throw std::runtime_error("Failed to read universe parameters");
    }

    if (numBodies < 0) {
        throw std::runtime_error("Invalid number of bodies");
    }
    if (universeRadius <= 0) {
        throw std::runtime_error("Universe radius must be greater than zero");
    }

    bodies.clear();
    for (size_t i = 0; i < numBodies; ++i) {
        double x, y, vx, vy, mass;
        std::string imageFilename;

        if (!(is >> x >> y >> vx >> vy >> mass >> imageFilename)) {
            throw std::runtime_error("Failed to read celestial body data at index "
            + std::to_string(i));
        }
        if (mass < 0) {
            throw std::runtime_error("Invalid mass for celestial body at index "
            + std::to_string(i));
        }
        if (imageFilename.empty()) {
            throw std::runtime_error("Missing image filename for celestial body at index "
            + std::to_string(i));
        }
        auto body = std::make_shared<CelestialBody>(x, y, vx, vy, mass,
        imageFilename, universeRadius, windowSize);
        bodies.push_back(body);
    }
}


size_t Universe::size() const {
    return numBodies;
}
double Universe::radius() const {
    return universeRadius;
}

const CelestialBody& Universe::operator[](size_t i) const {
    if (i >= numBodies) {
        throw std::out_of_range("Index out of range");
    }
    return *bodies[i];
}

void Universe::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for (const auto& body : bodies) {
        window.draw(*body, states);
    }
}

std::istream& operator>>(std::istream& is, Universe& uni) {
    // Read number of bodies and universe radius
    if (!(is >> uni.numBodies >> uni.universeRadius)) {
        throw std::runtime_error("Failed to read universe parameters");
    }

    if (uni.numBodies < 0) {
        throw std::runtime_error("Invalid number of bodies");
    }
    if (uni.universeRadius <= 0) {
        throw std::runtime_error("Universe radius must be greater than zero");
    }

    uni.bodies.clear();

    for (size_t i = 0; i < uni.numBodies; ++i) {
        auto body = std::make_shared<CelestialBody>();
        is >> *body;

        if (is.fail()) {
            throw std::runtime_error("Failed to read celestial body data at index"
            + std::to_string(i));
        }
        body->setUniverseRadius(uni.universeRadius);
        uni.bodies.push_back(body);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& uni) {
    os << uni.numBodies << " " << uni.universeRadius << std::endl;
    for (const auto& body : uni.bodies) {
        os << *body << std::endl;
    }
    return os;
}

void Universe::step(double dt) {
    const double G = 6.67e-11;  // gravitational constant
    std::vector<double> fx(numBodies, 0.0);
    std::vector<double> fy(numBodies, 0.0);
    std::vector<double> new_x(numBodies);
    std::vector<double> new_y(numBodies);
    std::vector<double> new_vx(numBodies);
    std::vector<double> new_vy(numBodies);

    for (size_t i = 0; i < numBodies; ++i) {
        sf::Vector2f pos_i = bodies[i]->position();
        // sf::Vector2f vel_i = bodies[i]->velocity();
        float mass_i = bodies[i]->mass();

        for (size_t j = 0; j < numBodies; ++j) {
            if (i == j) continue;
            sf::Vector2f pos_j = bodies[j]->position();
            float mass_j = bodies[j]->mass();

            double dx = pos_j.x - pos_i.x;
            double dy = pos_j.y - pos_i.y;

            double r_squared = dx * dx + dy * dy + 1e-10;
            double r = std::sqrt(r_squared);

            double force = G * mass_i * mass_j / r_squared;

            fx[i] += force * dx / r;
            fy[i] += force * dy / r;
        }
    }

    for (size_t i = 0; i < numBodies; ++i) {
        sf::Vector2f pos_i = bodies[i]->position();
        sf::Vector2f vel_i = bodies[i]->velocity();
        float mass_i = bodies[i]->mass();

        double ax = fx[i] / mass_i;
        double ay = fy[i] / mass_i;

        new_vx[i] = vel_i.x + ax * dt;
        new_vy[i] = vel_i.y + ay * dt;

        new_x[i] = pos_i.x + new_vx[i] * dt;
        new_y[i] = pos_i.y + new_vy[i] * dt;
    }

    for (size_t i = 0; i < numBodies; ++i) {
        bodies[i]->setPosition(new_x[i], new_y[i]);
        bodies[i]->setVelocity(new_vx[i], new_vy[i]);
    }
}
}  // namespace NB
