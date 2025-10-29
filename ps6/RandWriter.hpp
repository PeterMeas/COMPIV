// Copyright 2025 PETER
#include <string>
#include <random>
#include <iostream>
#include <map>

class RandWriter {
 public:
    //  Create a Markov model of order k from given text
    //  Assume that text has length at least k.
    RandWriter(const std::string& str, size_t k);

    size_t orderK() const;  //  Order k of Markov model

    //  Number of occurences of kgram in text
    //  Throw an exception if kgram is not length k
    int freq(const std::string& kgram) const;
    //  Number of times that character c follows kgram
    //  if order=0, return num of times that char c appears
    //  (throw an exception if kgram is not of length k)
    int freq(const std::string& kgram, char c) const;

    //  Random character following given kgram
    //  (throw an exception if kgram is not of length k)
    //  (throw an exception if no such kgram)
    char kRand(const std::string& kgram);
    //  Generate a string of length L characters by simulating a trajectory
    //  through the corresponding Markov chain. The first k characters of
    //  the newly generated string should be the argument kgram.
    //  Throw an exception if kgram is not of length k.
    //  Assume that L is at least k
    std::string generate(const std::string& kgram, size_t l);

  friend std::ostream& operator<<(std::ostream& os, const RandWriter& writer);

 private:
size_t k;  // order k
std::string text;  // original text
//  key : kgram string value: # of occurances
std::map<std::string, int> kgramFreq;  // map for kgram freq
//  map to store k+1 gram freq (k-gram followed by char)
std::map<std::string, int> kPlusOneGramFreq;  // key k+1 gram, value: count occurances
std::string alphabet;  // store unique char in txt
std::mt19937 rng;  // random #


    //  Private member variables go here
};
std::ostream& operator<<(std::ostream& os, const RandWriter& writer);
