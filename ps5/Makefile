CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

all: EDistance

EDistance: main.o EDistance.o
	$(CXX) $^ -o $@ $(LDFLAGS)

EDistance.a: EDistance.o
	ar rcs $@ $^

main.o: main.cpp EDistance.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

EDistance.o: EDistance.cpp EDistance.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o EDistance EDistance.a test

lint:
	cpplint --repository=. *.cpp *.hpp

.PHONY: all clean lint