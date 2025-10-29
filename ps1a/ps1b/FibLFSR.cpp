// Copyright 2025 Peter Meas //
#include "FibLFSR.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

std::ostream& PhotoMagic::operator<<(std::ostream& os, const FibLFSR& ls) {
    os << ls.registerBits;
    return os;
}

PhotoMagic::FibLFSR::FibLFSR(const std::string& seed) {
    if ((seed.length()) != 16) {
        throw std::invalid_argument("Seed must be 16 bits long");
            }
        for (char c : seed) {
            if (c != '0' && c != '1') {
                    throw std::invalid_argument("Seed must only be 0s and 1s");
        }
    }
    registerBits = std::bitset<16>(seed);
}

int PhotoMagic::FibLFSR::step() {
    int leftmostBit = registerBits[15];

    int tap13 = registerBits[13];
    int tap12 = registerBits[12];
    int tap10 = registerBits[10];
    int feedbackBit_ = leftmostBit ^ tap13 ^ tap12 ^ tap10;
    registerBits.operator<<=(1);
    registerBits.set(0, feedbackBit_);
    return feedbackBit_;
}

int PhotoMagic::FibLFSR::generate(int k) {
    if (k < 0) {
        throw std::invalid_argument("Negative input");
    }
    if (k > 16) {
        throw std::invalid_argument("Higher than 16 bits");
    }

    int extractedBits = 0;
    for (int i = 0; i < k; i++) {
        extractedBits = (extractedBits * 2) + step();
    }
    return extractedBits;
}
