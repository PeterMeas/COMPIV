CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

all: TextWriter TextWriter.a test

TextWriter: TextWriter.cpp RandWriter.o
	$(CXX) $(CXXFLAGS) -o TextWriter TextWriter.cpp RandWriter.o

TextWriter.a: RandWriter.o
	ar rcs TextWriter.a RandWriter.o

RandWriter.o: RandWriter.cpp RandWriter.hpp
	$(CXX) $(CXXFLAGS) -c RandWriter.cpp

test: test.cpp RandWriter.o
	$(CXX) $(CXXFLAGS) -o test test.cpp RandWriter.o $(LDFLAGS)

lint:
	cpplint --repository=. *.cpp *.hpp

clean:
	rm -f *.o TextWriter TextWriter.a test

.PHONY: all lint clean