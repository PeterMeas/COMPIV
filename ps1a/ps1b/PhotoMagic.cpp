// Copyright 2025 Peter Meas //
#include "PhotoMagic.hpp"
#include <fstream>

void PhotoMagic::transform(sf::Image& img, FibLFSR* lfsr) {
    // test : std::cout << "lfsr: "<< lfsr->generate(9) <<std::endl;
    sf::Color p;
    for (unsigned int y = 0; y < img.getSize().y; y++) {
        for (unsigned int x=0; x < img.getSize().x; x++) {
            p = img.getPixel(x, y);
            int red = p.r;
            int green = p.g;
            int blue = p.b;

            int xorred = red ^ lfsr->generate(10);
            int xorgreen = green ^ lfsr->generate(10);
            int xorblue = blue ^ lfsr->generate(10);

            sf::Color newP(xorred, xorgreen, xorblue);
            img.setPixel(x, y, newP);
        }
    }
}
