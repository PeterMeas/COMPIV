CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g  
LIB = -lboost_unit_test_framework -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

.PHONY: all clean lint

CXXFLAGS = $(CFLAGS)

all: PhotoMagic test lint

PhotoMagic: main.cpp PhotoMagic.a
	$(CC) $(CFLAGS) main.cpp PhotoMagic.a -o PhotoMagic $(LIB)

test: test.cpp PhotoMagic.a
	$(CC) $(CFLAGS) test.cpp PhotoMagic.a -o test $(LIB)

PhotoMagic.a: FibLFSR.o PhotoMagic.o
	ar rcs PhotoMagic.a FibLFSR.o PhotoMagic.o

FibLFSR.o: FibLFSR.cpp FibLFSR.hpp
	$(CC) $(CFLAGS) -c FibLFSR.cpp -o FibLFSR.o

clean:
	rm -f *.o *.a PhotoMagic test

lint:
	cpplint --repository=. *.cpp *.hpp
