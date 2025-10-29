// Copyright 2025 Mohamed Bouchtout and Peter Meas

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "EDistance.hpp"

EDistance::EDistance(const std::string& s1, const std::string& s2) {
    _s1 = s1;
    _s2 = s2;

    _m = _s1.length();
    _n = _s2.length();

    //  allocater matrix
    _matrix.resize(_m + 1, std::vector<int>((_n) + 1, 0));
}

int EDistance::penalty(char a, char b) {
    return a == b ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    if (a <= b && a <= c) {
        return a;
    } else if (b <= a && b <= c) {
        return b;
    } else {
        return c;
    }
}

int EDistance::optDistance() {
    for (int j = 0; j <= _n; j++) {
        _matrix[_m][j] = 2 * (_n - j);
    }

    for (int i =0; i <= _m; i++) {
        _matrix[i][_n] = 2 * (_m - i);
    }

    for (int i = _m - 1; i >= 0; i--) {
        for (int j = _n - 1; j >= 0; j--) {
            int match = _matrix[i+1][j+1] + penalty(_s1[i], _s2[j]);

            int del = _matrix[i+1][j] + 2;
            int insert = _matrix[i][j+1] + 2;

            _matrix[i][j] = min3(match, del, insert);
        }
    }

    return _matrix[0][0];
}

std::string EDistance::alignment() {
    std::string output;
    //  std::string s1;
    //  std::string s2;
    int i = 0;
    int j = 0;

    while (i < _m && j < _n) {  // loop through strings, start at [0][0]
        // 3 cases to handle
        //  match or mismatch (diagnoal )
        if (_matrix[i][j] == _matrix[i+1][j+1] + penalty(_s1[i], _s2[j])) {
            output = output + _s1[i];
            output = output + " ";
            output = output + _s2[j];
            output = output + " ";
            output = output + std::to_string(penalty(_s1[i], _s2[j]));
            output = output + "\n";
            i++;
            j++;
            //  format :
            //  string1  string2  cost
            //  A        A       0
        } else if (_matrix[i][j] == _matrix[i+1][j] + 2) {
            // gap s2 (move down)
            //  align char in s1 with a gap
            output = output + _s1[i];
            output = output + " ";
            output = output + "-";
            output += " ";
            output += "2";
            output += "\n";
            i++;
        } else {  //  gap in s1
            output += "-";
            output += " ";
            output += _s2[j];
            output += " ";
            output += "2";
            output += "\n";
            j++;
        }
    }

    while (i < _m) {
        output += _s1[i];
        output += " ";
        output += "-";
        output += " ";
        output += "2";
        output += "\n";
        i++;
    }

    while (j < _n) {
        output += "-";
        output += " ";
        output += _s2[j];
        output += "2";
        output += "\n";
        j++;
    }

    return output;
}
