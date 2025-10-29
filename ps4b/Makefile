CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -pedantic -g
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lboost_unit_test_framework

all: Sokoban Sokoban.a test

Sokoban: main.o Sokoban.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(CXXFLAGS)

Sokoban.a: Sokoban.o
	ar rcs $@ $^

main.o: main.cpp Sokoban.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

Sokoban.o: Sokoban.cpp Sokoban.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: test.o Sokoban.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(CXXFLAGS)

test.o: test.cpp Sokoban.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o Sokoban Sokoban.a test
lint:
	cpplint --repository=. *.cpp *.hpp

.PHONY: all clean lint