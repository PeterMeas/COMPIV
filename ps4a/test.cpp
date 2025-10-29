// Copyright 2025 Peter Meas
#define BOOST_TEST_MODULE SokobanTests
#include <fstream>
#include <sstream>
#include "Sokoban.hpp"
#include <boost/test/included/unit_test.hpp>


void createTestLevel(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}


BOOST_AUTO_TEST_CASE(TestBasicMovement) {
    createTestLevel("test_movement.lvl",
                    "5 5\n"
                    "#####\n"
                    "#...#\n"
                    "#.@.#\n"
                    "#...#\n"
                    "#####\n");

    SB::Sokoban sokoban("test_movement.lvl");

    // Test initial position
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);

    // Test movement in all directions
    sokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);

    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 3u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);

    sokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 3u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);

    sokoban.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);
}

BOOST_AUTO_TEST_CASE(TestWallCollision) {
    createTestLevel("test_wall.lvl",
                    "5 5\n"
                    "#####\n"
                    "#.@.#\n"
                    "#...#\n"
                    "#...#\n"
                    "#####\n");

    SB::Sokoban sokoban("test_wall.lvl");

    // Test initial position
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);

    // Test wall collision (should not move)
    sokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);
}

BOOST_AUTO_TEST_CASE(TestBoxPushing) {
    createTestLevel("test_box.lvl",
                    "5 5\n"
                    "#####\n"
                    "#...#\n"
                    "#.@A#\n"
                    "#...#\n"
                    "#####\n");

    SB::Sokoban sokoban("test_box.lvl");

    // Test push box to the right (should move)
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);
    // Reset and test push box against wall (should not move)
    sokoban.reset();
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);
}
BOOST_AUTO_TEST_CASE(TestWinCondition) {
    createTestLevel("test_win.lvl",
                    "5 5\n"
                    "#####\n"
                    "#...#\n"
                    "#.@A#\n"
                    "#..a#\n"
                    "#####\n");
    SB::Sokoban sokoban("test_win.lvl");
    // Initially not won
    BOOST_CHECK_EQUAL(sokoban.isWon(), false);
    // Push box to storage to win
    sokoban.movePlayer(SB::Direction::Up);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Down);
    // should be won
    BOOST_CHECK_EQUAL(sokoban.isWon(), true);
}

BOOST_AUTO_TEST_CASE(TestReset) {
    createTestLevel("test_reset.lvl",
                    "5 5\n"
                    "#####\n"
                    "#a..#\n"
                    "#.@A#\n"
                    "#...#\n"
                    "#####\n");
    SB::Sokoban sokoban("test_reset.lvl");
    // Record initial position
    sf::Vector2u initialPos = sokoban.playerLoc();
    // Move player
    sokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK(sokoban.playerLoc() != initialPos);
    sokoban.reset();
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, initialPos.x);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, initialPos.y);
}
