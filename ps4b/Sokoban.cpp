// Copyright 2025 Peter Meas
#include "Sokoban.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

namespace SB {

Sokoban::Sokoban() {
}

Sokoban::Sokoban(const std::string& filename) {
    std::ifstream infile(filename);
    if (infile) {
        infile >> *this;
    }
}

unsigned int Sokoban::pixelHeight() const {
    return height() * TILE_SIZE;
}

unsigned int Sokoban::pixelWidth() const {
    return width() * TILE_SIZE;
}

unsigned int Sokoban::height() const {
    return m_height;
}

unsigned int Sokoban::width() const {
    return m_width;
}

sf::Vector2u Sokoban::playerLoc() const {
    return m_playerLoc;
}

bool Sokoban::isWon() const {
    // part a d o nothing, part b movement logic

    auto BoxNotOnStorage = [](char c) { return c == 'A'; };
    int boxesNotOnStorage = std::count_if(m_grid.begin(), m_grid.end(), BoxNotOnStorage);

    auto StorageWithoutBox = [](char c) { return c == 'a'; };
    int emptyCount = std::count_if(m_grid.begin(), m_grid.end(), StorageWithoutBox);

    auto BoxOnStorage = [](char c) { return c == '1'; };
    int boxesOnStorage = std::count_if(m_grid.begin(), m_grid.end(), BoxOnStorage);

    int totalStor = emptyCount + boxesOnStorage;
    int totalBox = boxesOnStorage + boxesNotOnStorage;

    if (totalBox > totalStor) {
        return emptyCount == 0;
    } else {
        return boxesNotOnStorage == 0;
    }
}

void Sokoban::movePlayer(Direction dir) {
    // part a do nothing, part b movnig lopgic
    sf::Vector2u newLocation = m_playerLoc;

    switch (dir) {
        case Direction::Up:
            if (newLocation.y > 0) newLocation.y--;
            break;
        case Direction::Down:
            if (newLocation.y < m_height - 1) newLocation.y++;
            break;
        case Direction::Left:
            if (newLocation.x > 0) newLocation.x--;
            break;
        case Direction::Right:
            if (newLocation.x < m_width - 1) newLocation.x++;
            break;
    }
    unsigned int index = newLocation.y * m_width + newLocation.x;
    char& tarCell = m_grid[index];

    if (tarCell == '.' || tarCell == 'a') {  //  case where target cell is empty
        m_playerLoc = newLocation;
    } else if (tarCell == '#') {  // target cell is a wall
        // Cant move, wall
        return;
    } else if (tarCell == 'A' || tarCell == '1') {
        // box or box on storage, lets try to push it
        // box pushing logic

        sf::Vector2u boxNewPos = newLocation;

        switch (dir) {
            case Direction::Up:
            if (boxNewPos.y > 0) boxNewPos.y--;
            break;
            case Direction::Down:
            if (boxNewPos.y < m_height - 1) boxNewPos.y++;
            break;
            case Direction::Left:
            if (boxNewPos.x > 0) boxNewPos.x--;
            break;
            case Direction::Right:
            if (boxNewPos.x < m_width - 1) boxNewPos.x++;
            break;
        }
        char& boxTarCell = m_grid[boxNewPos.y *
        m_width + boxNewPos.x];  // . get character at box new pos
        if (boxTarCell == '.' || boxTarCell == 'a') {
            // . box can be pushed
            if (boxTarCell == '.') {
                boxTarCell = 'A';
            } else {
                boxTarCell = '1';
            }
            if (tarCell == 'A') {
                tarCell = '.';
            } else {
                tarCell = 'a';
            }
            m_playerLoc = newLocation;
        }
    }
}

void Sokoban::reset() {
    // reset game
    m_grid = m_initialGrid;
    m_playerLoc = m_initialPlayerLoc;
}

void Sokoban::undo() {
    // Optional
}

void Sokoban::redo() {
    // Optional
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    static sf::Texture wallTexture, floorTexture, boxTexture, storageTexture,
    boxOnStorageTexture, playerTexture;
    static bool texturesLoaded = false;
    if (!texturesLoaded) {
        wallTexture.loadFromFile("block_06.png");
        floorTexture.loadFromFile("ground_01.png");
        boxTexture.loadFromFile("crate_03.png");
        storageTexture.loadFromFile("ground_04.png");
        playerTexture.loadFromFile("player_05.png");
        texturesLoaded = true;
    }

    // Create a sprite for drawing
    sf::Sprite sprite;
    // Draw the grid
    for (unsigned int y = 0; y < height(); ++y) {
        for (unsigned int x = 0; x < width(); ++x) {
            sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            switch (m_grid[y * width() + x]) {
                case '#':  // a Wall
                    sprite.setTexture(wallTexture);
                    break;
                case '.':  // empty  space
                    sprite.setTexture(floorTexture);
                    break;
                case 'A':  // box
                    sprite.setTexture(floorTexture);
                    target.draw(sprite, states);
                    sprite.setTexture(boxTexture);
                    break;
                case 'a':  // Storage location
                    sprite.setTexture(storageTexture);
                    break;
                case '1':  // Box on storage
                    sprite.setTexture(storageTexture);
                    target.draw(sprite, states);
                    sprite.setTexture(boxTexture);
                    break;
                default:
                    sprite.setTexture(floorTexture);
                    break;
            }
            // Draw  sprite
            target.draw(sprite, states);
        }
    }
    // draw the player separately (so it's always on top)
    sprite.setTexture(playerTexture);
    sprite.setPosition(m_playerLoc.x * TILE_SIZE, m_playerLoc.y * TILE_SIZE);
    target.draw(sprite, states);

    if (isWon()) {
    sf::Font font;
    font.loadFromFile("arial.ttf");

    sf::Text text("YOU WONONN!NMN!N!N!N1", font, 48);
    text.setFillColor(sf::Color::Green);
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width /2 , textRect.height / 2);
    text.setPosition(pixelWidth()/2, pixelHeight()/2);

    target.draw(text, states);

    } else {
        sprite.setTexture(playerTexture);
        sprite.setPosition(m_playerLoc.x * TILE_SIZE, m_playerLoc.y * TILE_SIZE);
        target.draw(sprite, states);
    }
}

std::ostream& operator<<(std::ostream& out, const Sokoban& s) {
    out << s.height() << " " << s.width() << std::endl;

    for (unsigned int y = 0; y < s.height(); ++y) {
        for (unsigned int x = 0; x < s.width(); ++x) {
            // Check if this is the player's position
            if (x == s.playerLoc().x && y == s.playerLoc().y) {
                out << '@';
            } else {
                out << s.m_grid[y * s.width() + x];
            }
        }
        out << std::endl;
    }

    return out;
}
std::istream& operator>>(std::istream& in, Sokoban& s) {
    in >> s.m_height >> s.m_width;
    std::string line;
    std::getline(in, line);
    s.m_grid.resize(s.m_height * s.m_width);
    s.m_initialGrid.resize(s.m_height * s.m_width);
    for (unsigned int y = 0; y < s.m_height; ++y) {
        std::getline(in, line);
        for (unsigned int x = 0; x < s.m_width && x < line.length(); ++x) {
            char cell = line[x];
            // handle the player position separately
            if (cell == '@') {
                s.m_playerLoc = sf::Vector2u(x, y);
                s.m_initialPlayerLoc = sf::Vector2u(x, y);
                cell = '.';  // player standing on an empty space
            }

            s.m_grid[y * s.m_width + x] = cell;
            s.m_initialGrid[y * s.m_width + x] = cell;
        }
    }
    return in;
}

}  // namespace SB
