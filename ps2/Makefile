CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g  
LIB = -lboost_unit_test_framework -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: Triangle lint 

Triangle: main.cpp Triangle.o
	$(CC) $(CFLAGS) main.cpp Triangle.o -o Triangle $(LIB)

Triangle.o: triangle.cpp triangle.hpp
	$(CC) $(CFLAGS) -c triangle.cpp -o Triangle.o

lint:
	cpplint --repository=. *.cpp *.hpp
clean:
	rm -f *.o *.a Triangle