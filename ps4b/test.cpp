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
/*
BOOST_AUTO_TEST_CASE(TestBasicMovement) {
    createTestLevel("test_movement.lvl",
                    "5 5\n"
                    "#####\n"
                    "#...#\n"
                    "#.@.#\n"
                    "#...#\n"
                    "#####\n");
    SB::Sokoban sokoban("test_movement.lvl");
    //  initial position
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);
    // Create a new instance for each movement
    // Test Up movement
    SB::Sokoban sokobanUp("test_movement.lvl");
    sokobanUp.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(sokobanUp.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokobanUp.playerLoc().y, 2u);
    // test right movement
    SB::Sokoban sokobanRight("test_movement.lvl");
    sokobanRight.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokobanRight.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokobanRight.playerLoc().y, 2u);
    // Test Down movement
    SB::Sokoban sokobanDown("test_movement.lvl");
    sokobanDown.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(sokobanDown.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokobanDown.playerLoc().y, 2u);
    // Test Left movement
    SB::Sokoban sokobanLeft("test_movement.lvl");
    sokobanLeft.movePlayer(SB::Direction::Left);
    BOOST_CHECK_EQUAL(sokobanLeft.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokobanLeft.playerLoc().y, 2u);
}*/


BOOST_AUTO_TEST_CASE(TestOutOfScreen) {
    createTestLevel("test_out_of_screen.lvl",
                    "5 5\n"
                    "#####\n"
                    "#.@.#\n"
                    "#...#\n"
                    "#...#\n"
                    "#####\n");

    SB::Sokoban sokoban("test_out_of_screen.lvl");
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);

    //  check to make sure player doesnt escape bounds of window
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

    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);  // a2
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);  // 1
}

BOOST_AUTO_TEST_CASE(TestBoxBoundaryPushing) {
    createTestLevel("test_box_boundary.lvl",
                    "5 5\n"
                    "..@A.\n"
                    ".....\n"
                    ".....\n"
                    ".....\n"
                    ".....\n");

    SB::Sokoban sokoban("test_box_boundary.lvl");

    // Test initial position
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 0u);

    // Try to push box off screen
    sokoban.movePlayer(SB::Direction::Right);
    // Box should stop at the boundary, player should move up to the box
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 0u);

    // Try to push box off screen again (should not move)
    sokoban.movePlayer(SB::Direction::Right);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 0u);
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

BOOST_AUTO_TEST_CASE(TestManyTargets) {
    createTestLevel("test_many_targets.lvl",
                    "7 7\n"
                    "#######\n"
                    "#.....#\n"
                    "#.aaaa#\n"
                    "#.@A..#\n"
                    "#.....#\n"
                    "#.....#\n"
                    "#######\n");
    SB::Sokoban sokoban("test_many_targets.lvl");
    BOOST_CHECK_EQUAL(sokoban.isWon(), false);

    // Push box to a target
    sokoban.movePlayer(SB::Direction::Down);
    sokoban.movePlayer(SB::Direction::Right);
    sokoban.movePlayer(SB::Direction::Up);
    BOOST_CHECK_EQUAL(sokoban.isWon(), true);
}

BOOST_AUTO_TEST_CASE(TestSymbolParse) {
    createTestLevel("test_symbols.lvl",
                    "7 7\n"
                    "#######\n"
                    "#.@...#\n"
                    "#.A...#\n"
                    "#.a...#\n"
                    "#.B...#\n"  // Ensure capital letters for boxes are parsed
                    "#.b...#\n"  // Ensure lowercase letters for targets are parsed
                    "#######\n");
    SB::Sokoban sokoban("test_symbols.lvl");
    // Check if player position is correct
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 1u);
    // Try to move to check if parsing worked properly
    sokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);
    // Try to push a box
    sokoban.movePlayer(SB::Direction::Down);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().x, 2u);
    BOOST_CHECK_EQUAL(sokoban.playerLoc().y, 2u);
}
