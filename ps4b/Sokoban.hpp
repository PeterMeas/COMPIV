// Copyright 2025 Peter Meas
#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

namespace SB {
enum class Direction {
    Up, Down, Left, Right
};

class Sokoban : public sf::Drawable {
 public:
friend std::ostream& operator<<(std::ostream& out, const Sokoban& s);
friend std::istream& operator>>(std::istream& in, Sokoban& s);
    static const int TILE_SIZE = 64;

    Sokoban();
    explicit Sokoban(const std::string&);  // Optional

    unsigned int pixelHeight() const;  // Optional
    unsigned int pixelWidth() const;  // Optional

    unsigned int height() const;
    unsigned int width() const;

    sf::Vector2u playerLoc() const;

    bool isWon() const;

    void movePlayer(Direction dir);
    void reset();

    void undo();  // Optional XC
    void redo();  // Optional XC

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    sf::Vector2u m_playerLoc;
    sf::Vector2u m_initialPlayerLoc;
    std::vector<char> m_grid;
    std::vector<char> m_initialGrid;
};

}  // namespace SB
