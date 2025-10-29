CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g  
LIB = -lboost_unit_test_framework -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system

all: NBody NBody.a test

NBody: main.o CelestialBody.o Universe.o
	$(CC) $(CFLAGS) -o NBody main.o CelestialBody.o Universe.o $(LIB)

NBody.a: main.o CelestialBody.o Universe.o
	ar rvs NBody.a main.o CelestialBody.o Universe.o

main.o: main.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c main.cpp

CelestialBody.o: CelestialBody.cpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c CelestialBody.cpp

Universe.o: Universe.cpp Universe.hpp CelestialBody.hpp
	$(CC) $(CFLAGS) -c Universe.cpp

test: test.o CelestialBody.o Universe.o
	$(CC) $(CFLAGS) -o test test.o CelestialBody.o Universe.o $(LIB)

test.o:	test.cpp CelestialBody.hpp Universe.hpp
	$(CC) $(CFLAGS) -c test.cpp

lint:
	cpplint --repository=. *.cpp *.hpp
clean:
	rm -f *.o *.a NBody test