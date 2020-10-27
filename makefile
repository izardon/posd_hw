.PHONY: dirs clean

CC = g++
SRC = src/rectangle.h src/ellipse.h src/triangle.h src/compound_shape.h \
			src/iterator.h src/null_iterator.h src/shape_iterator.h \
			src/utility.h
TEST = test/ut_rectangle.h test/ut_ellipse.h test/ut_triangle.h \
				test/ut_compound_shape.h test/ut_iterator.h test/ut_utility.h

all: dirs ut_main

dirs:
			mkdir -p bin
			mkdir -p obj

ut_main: test/ut_main.cpp shape.o $(TEST) $(SRC)
	$(CC) -Wfatal-errors test/ut_main.cpp -o bin/ut_main obj/shape.o -lgtest -lpthread

shape.o: src/shape.cpp
	$(CC) -c src/shape.cpp -o obj/shape.o

clean:
			rm -f bin/*
			rm -f obj/*

# $@：目前的目標項目名稱。
# $<：代表目前的相依性項目。
# $*：代表目前的相依性項目，但不含副檔名。
# $?：代表需要重建（被修改）的相依性項目。
