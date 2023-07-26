CC=gcc
FLAGS=-Wall -Wextra -g -std=c++17 -Werror
GCOV=--coverage
C=*.cc
A=s21_calculator.a
O=*.o
GTEST=gtest
OS=$(shell uname)

ifeq ($(OS), Darwin)
	LIBFLAGS = -lm -lgtest -lstdc++
else
	LIBFLAGS=-lstdc++ `pkg-config --cflags --libs gtest` -lm
endif

all: install

install:
	cd ./Calculator/Build && qmake ../ && make all && rm Makefile *.o *.h *.cpp

uninstall:
	rm -rf ./Calculator/Build/*

dvi:
	open Page/page.html

dist:
	tar -zcf $(TAR) Calculator/Build

test:
	$(CC) ./Calculator/Controller/$(C) ./Calculator/Model/$(C) $(FLAGS) $(C) $(LIBFLAGS) -o $(GTEST)
	./$(GTEST)
	
s21_calculator.a: clean
	$(CC) ./Calculator/Controller/$(C) ./Calculator/Model/$(C) $(FLAGS) -c $(C)
	ar rcs $(A) $(O)

gcov_report: s21_calculator.a
	$(CC) $(FLAGS) $(GCOV) $(C) $(A) $(LIBFLAGS) -o $(GTEST)
	./$(GTEST)
	lcov -t "./test" -o report.info --ignore-errors mismatch --no-external -c -d .
	genhtml -o report report.info
	open ./report/index.html

leaks:
ifeq ($(OS), Darwin)
	leaks -atExit -- ./$(GTEST)
else
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(GTEST)
endif

clean:
	rm -rf *.a *.o *.out gtest
	rm -rf *.info  *.gcda *.gcno -rf *.gcov -rf *dSYM
	rm -rf report/ && rm -rf *.
