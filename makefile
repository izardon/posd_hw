.PHONY: dirs clean

SRC = src/rectangle.h src/ellipse.h src/triangle.h src/sort.h src/terminal.h
TEST = test/ut_rectangle.h test/ut_ellipse.h test/ut_triangle.h test/ut_sort.h test/ut_terminal.h

all: dirs main ut_main

main : src/main.cpp $(SRC)
	g++ -Wfatal-errors src/main.cpp -o bin/geo

ut_main: test/ut_main.cpp $(TEST) $(SRC)
	g++ -Wfatal-errors test/ut_main.cpp -o bin/ut_main -lgtest -lpthread

dirs:
			mkdir -p bin

clean:
			rm -f bin/*
