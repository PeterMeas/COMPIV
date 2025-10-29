CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror -Wextra -pedantic -g
LDFLAGS = -lboost_date_time

all: ps7

ps7: ps7.cpp
	$(CXX) $(CXXFLAGS) ps7.cpp -o ps7 $(LDFLAGS)

lint:
	cpplint ps7.cpp

clean:
	rm -f ps7 *.o

.PHONY: all clean lint