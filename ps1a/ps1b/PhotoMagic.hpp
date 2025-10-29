// Copyright 2025 Peter Meas //
#pragma once

#include <SFML/Graphics.hpp>
#include "./FibLFSR.hpp"

namespace PhotoMagic {
void transform(sf::Image& img, FibLFSR* lfsr);

}
