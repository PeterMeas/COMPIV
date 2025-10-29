// Copyright 2022
// By Dr. Rykalova
// Editted by Dr. Daly
// test.cpp for PS1a
// updated 1/8/2024

#include <iostream>
#include <string>

#include "./FibLFSR.hpp"
#include "./PhotoMagic.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <./boost/test/unit_test.hpp>



using PhotoMagic::FibLFSR;

BOOST_AUTO_TEST_CASE(testStepInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testStep2) {
  FibLFSR lfsr("0110110001101100");
  BOOST_CHECK_EQUAL(lfsr.step(), 0);
  BOOST_CHECK_EQUAL(lfsr.step(), 0);
  BOOST_CHECK_EQUAL(lfsr.step(), 1);
}


BOOST_AUTO_TEST_CASE(testGenerateInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}

BOOST_AUTO_TEST_CASE(testGenerate1) {
  FibLFSR V("1011011000110110");
  std::ostringstream os;
  os << V;
  BOOST_CHECK_EQUAL(V.generate(5), 3);
  std::ostringstream os_after3;
  os_after3 << V;
  BOOST_REQUIRE_EQUAL(os_after3.str(), "1100011011000011");

  BOOST_CHECK_EQUAL(V.generate(5), 6);
  std::ostringstream os_after6;
  os_after6 << V;
  BOOST_REQUIRE_EQUAL(os_after6.str(), "1101100001100110");
  BOOST_CHECK_EQUAL(V.generate(5), 14);
  std::ostringstream os_after14;
  os_after14 << V;
  BOOST_REQUIRE_EQUAL(os_after14.str(), "0000110011001110");
}



BOOST_AUTO_TEST_CASE(testOutputOperator) {
    PhotoMagic::FibLFSR lfsr("0110110001101100");
    std::ostringstream os;
    os << lfsr;
    BOOST_CHECK_EQUAL(os.str(), "0110110001101100");

    lfsr.step();
    std::ostringstream os_after_step;
    os_after_step << lfsr;
    BOOST_REQUIRE_EQUAL(os_after_step.str(), "1101100011011000");
}

BOOST_AUTO_TEST_CASE(testInvalidConstructor) {
  BOOST_CHECK_THROW(FibLFSR invalid_lfsr("invalid_input"), std::invalid_argument);
  BOOST_CHECK_NO_THROW(FibLFSR valid_lfsr("1011011000110110"));
}

BOOST_AUTO_TEST_CASE(testInvalidGen) {
  FibLFSR lfsr("1011011000110110");
  BOOST_CHECK_THROW(lfsr.generate(-1), std::invalid_argument);
}
