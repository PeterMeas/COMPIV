// Copyright 2025 Peter Meas
#include <sstream>
#include <fstream>
#include "CelestialBody.hpp"
#include "Universe.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

namespace sf {
std::ostream& operator<<(std::ostream& os, const Vector2f& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}
}

NB::Universe createTestUniverse() {
    std::stringstream ss;
    ss << "2\n";  // Two bodies
    ss << "1.0e+11\n";  // Universe radius
    // Body 1: Sun-like body at center with zero velocity
    ss << "0.0 0.0 0.0 0.0 1.989e+30 sun.gif\n";
    // Body 2: Earth-like body with known position and velocity
    ss << "1.0e+11 0.0 0.0 3.0e+4 5.972e+24 earth.gif\n";

    NB::Universe universe;
    ss >> universe;
    return universe;
}

BOOST_AUTO_TEST_CASE(test_celestial_body_default_constructor) {
    NB::CelestialBody body;
    //  BOOST_CHECK_EQUAL(body.mass(), 0.0f);
    BOOST_CHECK_EQUAL(body.position(), sf::Vector2f(0, 0));
    BOOST_CHECK_EQUAL(body.velocity(), sf::Vector2f(0, 0));
}

BOOST_AUTO_TEST_CASE(test_celestial_body_initialization) {
    NB::CelestialBody body;
    BOOST_CHECK(body.position() == sf::Vector2f(0, 0));
    BOOST_CHECK(body.velocity() == sf::Vector2f(0, 0));
    std::istringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    input >> body;

    std::cout << "Body Mass: " << body.mass() << std::endl;
    //  check within 0.001 of expected value "boost_check_close"
    BOOST_CHECK_CLOSE(body.mass(), 5.9740e24f, 0.001f);
}

BOOST_AUTO_TEST_CASE(test_celestial_body_stream_operator) {
    NB::CelestialBody body;
    std::istringstream input("1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif");
    input >> body;

    BOOST_CHECK_CLOSE(body.mass(), 5.9740e24f, 0.001f);
    BOOST_CHECK_CLOSE(body.position().x, 1.4960e+11f, 0.001f);
    BOOST_CHECK_CLOSE(body.position().y, 0.0000, 0.0001);
    BOOST_CHECK_CLOSE(body.velocity().x, 0.0000, 0.001);
    BOOST_CHECK_CLOSE(body.velocity().y, 2.9800e+04, 0.001);
}

BOOST_AUTO_TEST_CASE(test_celestial_body_output_format) {
    NB::CelestialBody body;
    std::istringstream input("1.4960e+11 0.0000 0.0000 2.9800e+04 5.9740e+24 earth.gif");
    input >> body;

    std::ostringstream output;
    output << body;

    std::string expected = "1.496e+11 0 0 29800 5.974e+24 earth.gif";

    std::cout << "Expected: [" << expected << "]\n";
    std::cout << "Actual:   [" << output.str() << "]\n";

    BOOST_CHECK_EQUAL(output.str(), expected);
}

BOOST_AUTO_TEST_CASE(test_large_universe_radius) {
    std::ofstream largeRadiusFile("large_radius.txt");
    largeRadiusFile << "1\n";
    largeRadiusFile << "1.0e+20\n";
    largeRadiusFile
    << "1.4960e+11 0.0000e+00 0.0000e+00 2.9800e+04 5.9740e+24 earth.gif\n";  // Valid body
    largeRadiusFile.close();
    NB::Universe universe("large_radius.txt");
    BOOST_CHECK_CLOSE(universe.radius(), 1.0e+20, 0.001);
}

BOOST_AUTO_TEST_CASE(test_acceleration_computation) {
    NB::Universe universe = createTestUniverse();

    const double G = 6.67e-11;
    double mass_sun = 1.989e+30;
    double distance = 1.0e+11;

    double expected_acceleration = G * mass_sun / (distance * distance);

    double tiny_dt = 1.0;
    universe.step(tiny_dt);

    sf::Vector2f new_velocity = universe[1].velocity();

    double actual_acceleration = -(new_velocity.x - 0) / tiny_dt;

    BOOST_CHECK_CLOSE(actual_acceleration, expected_acceleration, 1.0);
}

BOOST_AUTO_TEST_CASE(t19) {
    std::stringstream ss;
    ss << "2\n";          // Two bodies
    ss << "2.5e+11\n";    // Universe radius
    // Two equal-mass bodies close to each other
    ss << "0.0 0.0 0.0 0.0 1.0e+25 body1.gif\n";
    ss << "1.0e+10 0.0 0.0 0.0 1.0e+25 body2.gif\n";

    // Create a uni with test bodies
    NB::Universe universe;
    ss >> universe;

    //  initial position
    sf::Vector2f initial_pos0 = universe[0].position();
    sf::Vector2f initial_pos1 = universe[1].position();

    // Run simm
    double dt = 50000.0;
    for (int i = 0; i < 3; i++) {
        universe.step(dt);
    }

    sf::Vector2f final_pos0 = universe[0].position();
    sf::Vector2f final_pos1 = universe[1].position();

    BOOST_CHECK_MESSAGE(final_pos0.x > initial_pos0.x,
                        "Body 0 should move toward Body 1 (right direction)");
    BOOST_CHECK_MESSAGE(final_pos1.x < initial_pos1.x,
        "Body 1 should move toward Body 0 (left direction)");
}

/* BOOST_AUTO_TEST_CASE(test_velocity_update) {
    NB::Universe universe = createTestUniverse();

    sf::Vector2f initial_velocity = universe[1].velocity();

    double dt = 1000.0;
    universe.step(dt);

    sf::Vector2f new_velocity = universe[1].velocity();

    BOOST_CHECK(new_velocity.x < initial_velocity.x);
    BOOST_CHECK_CLOSE(new_velocity.y, initial_velocity.y, 0.001);
} */
/*
BOOST_AUTO_TEST_CASE(test_order_of_operations) {
    NB::Universe universe = createTestUniverse();

    sf::Vector2f initial_earth_pos = universe[1].position();
    sf::Vector2f initial_sun_pos = universe[0].position();

    double dt = 25000.0;
    universe.step(dt);

    sf::Vector2f new_earth_pos = universe[1].position();
    sf::Vector2f new_sun_pos = universe[0].position();

    BOOST_CHECK(new_earth_pos.x < initial_earth_pos.x);
    BOOST_CHECK(new_sun_pos.x > initial_sun_pos.x);

    universe.step(dt);

    sf::Vector2f newest_earth_pos = universe[1].position();

    double first_displacement = initial_earth_pos.x - new_earth_pos.x;
    double second_displacement = new_earth_pos.x - newest_earth_pos.x;

    BOOST_CHECK(second_displacement > first_displacement);
}*/

/*BOOST_AUTO_TEST_CASE(test_energy_conservation) {
    NB::Universe universe = createTestUniverse();

    const double G = 6.67e-11;

    double mass_sun = universe[0].mass();
    double mass_earth = universe[1].mass();

    sf::Vector2f sun_pos = universe[0].position();
    sf::Vector2f earth_pos = universe[1].position();

    sf::Vector2f sun_vel = universe[0].velocity();
    sf::Vector2f earth_vel = universe[1].velocity();

    double dx = earth_pos.x - sun_pos.x;
    double dy = earth_pos.y - sun_pos.y;
    double r = sqrt(dx*dx + dy*dy);

    double sun_ke = 0.5 * mass_sun * (sun_vel.x*sun_vel.x + sun_vel.y*sun_vel.y);
    double earth_ke = 0.5 * mass_earth * (earth_vel.x*earth_vel.x + earth_vel.y*earth_vel.y);
    double initial_ke = sun_ke + earth_ke;

    double initial_pe = -G * mass_sun * mass_earth / r;

    double initial_total_energy = initial_ke + initial_pe;

    universe.step(100000.0);

    sun_pos = universe[0].position();
    earth_pos = universe[1].position();
    sun_vel = universe[0].velocity();
    earth_vel = universe[1].velocity();

    dx = earth_pos.x - sun_pos.x;
    dy = earth_pos.y - sun_pos.y;
    r = sqrt(dx*dx + dy*dy);

    sun_ke = 0.5 * mass_sun * (sun_vel.x*sun_vel.x + sun_vel.y*sun_vel.y);
    earth_ke = 0.5 * mass_earth * (earth_vel.x*earth_vel.x + earth_vel.y*earth_vel.y);
    double final_ke = sun_ke + earth_ke;

    double final_pe = -G * mass_sun * mass_earth / r;

    double final_total_energy = final_ke + final_pe;

    BOOST_CHECK_CLOSE(final_total_energy, initial_total_energy, 5.0);
}
*/
