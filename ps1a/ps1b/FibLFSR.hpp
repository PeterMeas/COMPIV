// Copyright 2025 Peter Meas //
#pragma once
#include <iostream>
#include <string>
#include <bitset>

namespace PhotoMagic {
class FibLFSR {
friend std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr);

 public:
    explicit FibLFSR(const std::string& seed);
    explicit FibLFSR(unsigned int seed);  // Optional

    static FibLFSR fromPassword(const std::string& password);  // Optional

    int step();
    int generate(int k);
 private:
      std::bitset<16> registerBits;
};
std::ostream& operator<<(std::ostream& os, const FibLFSR& lfsr);


}  // namespace PhotoMagic
