// Copyright 2025 Mohamed Bouchtout and Peter Meas

#pragma once

#include <string>
#include <vector>

class EDistance {
 public:
    EDistance(const std::string& s1, const std::string& s2);

    static int penalty(char a, char b);
    static int min3(int a, int b, int c);

    int optDistance();
    std::string alignment();
 private:
    std::string _s1;
    std::string _s2;
    int _m;
    int _n;
    std::vector<std::vector<int>> _matrix;
};
