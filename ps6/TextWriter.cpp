// Copyright 2025 Peter
#include <iostream>
#include <sstream>
#include <string>
#include "RandWriter.hpp"
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usuage: " << argv[0] << " k L" << std::endl;
        return 1;
    }

    int k = std::stoi(argv[1]);
    int L = std::stoi(argv[2]);

    std::string text;
    std::string line;

    while (std::getline(std::cin, line)) {
        text += line;
        text += '\n';
    }

    if (!text.empty() && text.back() == '\n') {
        text.pop_back();
    }

    RandWriter writer(text, k);
    std::string firstKgram = text.substr(0, k);
    std::string result = writer.generate(firstKgram, L);

    std::cout << result << std::endl;
    return 0;
}
