all: dirs ut_main

#declare variables
CC = g++
SRC = src/rectangle.h src/ellipse.h src/triangle.h src/compound_shape.h
TEST = test/ut_rectangle.h test/ut_ellipse.h test/ut_triangle.h test/ut_compound_shape.h

ut_main: test/ut_main.cpp $(TEST) $(SRC)
	$(CC) -c src/shape.cpp -o obj/shape.o
	$(CC) -Wfatal-errors test/ut_main.cpp -o bin/ut_main obj/shape.o -lgtest -lpthread

.PHONY: dirs clean

dirs:
			mkdir -p bin
			mkdir -p obj
clean:
			rm -f bin/*
