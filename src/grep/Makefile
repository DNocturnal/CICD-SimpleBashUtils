CC=gcc
FLAGS= -Werror -Wextra -Wall
OS=$(shell uname)

ifeq ($(OS), Linux)
	CHKFLAGS=-pthread -lrt -lm -lsubunit
else
	CHKFLAGS=
endif

GREP=s21_grep
TESTFILE=s21_grep_test

all: clean s21_grep

build: s21_grep

s21_grep: s21_grep.c s21_grep.h
	$(CC) $(FLAGS) $(GREP).c $(GREP).h -o s21_grep 

test: s21_grep
	sh $(TESTFILE).sh
	
clean:
	@rm -rf *.o *.out *.a ./$(GREP)

linter:
	@cp ../../materials/linters/CPPLINT.cfg ./
	@find . -name "*.c" -exec python3 ../../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

style:
	cppcheck --enable=all --suppress=missingIncludeSystem ../../src

leaks:
	CK_FORK=no leaks --atExit -- ./s21_grep
