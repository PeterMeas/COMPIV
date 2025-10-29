// Copyright 2025 Peter
#include "RandWriter.hpp"
#include <algorithm>

std::ostream& operator<<(std::ostream& os, const RandWriter& writer) {
    // Print order k
    os << "Order: " << writer.k << std::endl;
    // Print alphabet
    os << "Alphabet: ";
    std::for_each(writer.alphabet.begin(), writer.alphabet.end(), [&](char c) {
        if (c == '\n') os << "\\n";
        else if (c == '\t') os << "\\t";
        else if (c == ' ') os << "␣";
        else os << c;
    });

    os << std::endl;

    // Print k-gram frequencies
    os << "k-gram frequencies:" << std::endl;
    for (const auto& pair : writer.kgramFreq) {
        os << "  \"" << pair.first << "\": " << pair.second << std::endl;
    }

    // Print k+1-gram frequencies
    os << "k+1-gram frequencies:" << std::endl;
    for (const auto& pair : writer.kPlusOneGramFreq) {
        os << "  \"" << pair.first << "\": " << pair.second << std::endl;
    }

    return os;
}

RandWriter::RandWriter(const std::string& str, size_t k) {
    std::random_device rndm;  // use for seed gen
    rng = std::mt19937(rndm());
    this->text = str;
    this->k = k;
    if (str.length() < k) {
        throw std::invalid_argument("Text length must be at least k");
    }

    for (size_t i = 0; i < str.length(); i++) {
        // extract kgram starting a pos i
        std::string kgram;
        for (size_t j = 0; j < k; j++) {
            // get pos for the char at posiiton (i+j) % str.length , to handle wraparound
            kgram += str[(i+j) % str.length()];
            // add char to kgram
        }
        char newChar = str[(i+k) % str.length()];
        kgramFreq[kgram]++;
        kPlusOneGramFreq[kgram + newChar]++;

        if (alphabet.find(newChar) == std::string::npos) {
            alphabet += newChar;
        }
    }
}

size_t RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(const std::string& kgram) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must equal k");
    }

    auto it = kgramFreq.find(kgram);
    if (it != kgramFreq.end()) {
        return it->second;  // return INT freq count for THIS kgram
    } else {
        return 0;
    }
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must equal k");
    }
    if (k == 0) {
        int count = 0;
        for (char ch : text) {
            if (ch == c) {
                count++;
            }
        }
            return count;
    }

    std::string kplus;
    kplus = kgram + c;
    auto it = kPlusOneGramFreq.find(kplus);
    if (it != kPlusOneGramFreq.end()) {
        return it->second;
    } else {
        return 0;
    }
}

char RandWriter::kRand(const std::string& kgram) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must equal k");
    }
    if (freq(kgram) == 0) {
        throw std::invalid_argument("kgram not found in text");
    }

    std::vector<char> possibilities;
    std::vector<int> weights;

    //  For each character in the alphabet:
    for (char c : alphabet) {
        // get freq of char following kgram
        int frequency = freq(kgram, c);
        if (frequency > 0) {
            possibilities.push_back(c);
            weights.push_back(frequency);
        }
    }

    std::discrete_distribution<int> dist(weights.begin(), weights.end());
    return possibilities[dist(rng)];
}

std::string RandWriter::generate(const std::string& kgram, size_t L) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must equal k");
    }

    std::string result = kgram;

    //  gen L-k char
    for (size_t i = 0; i < L - k; ++i) {
        std::string currentKgram = result.substr(result.length() - k);

        char nextChar = kRand(currentKgram);

        result += nextChar;
    }
    return result;
}
