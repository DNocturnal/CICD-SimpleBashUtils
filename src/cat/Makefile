CC=gcc
FLAGS= -Werror -Wextra -Wall
OS=$(shell uname)

ifeq ($(OS), Linux)
	CHKFLAGS=-pthread -lrt -lm -lsubunit
else
	CHKFLAGS=
endif

CAT=s21_cat
TESTFILE=s21_cat_test

all: clean s21_cat

s21_cat: s21_cat.c s21_cat.h
	$(CC) $(FLAGS) $(CAT).c $(CAT).h -o s21_cat
	

test: $(CAT)
	sh $(TESTFILE).sh

clean:
	@rm -rf *.o *.out *.a ./$(CAT)

linter:
	@cp ../../materials/linters/CPPLINT.cfg ./
	@find . -name "*.c" -exec python3 ../../materials/linters/cpplint.py {} \;
	@find . -name "*.h" -exec python3 ../../materials/linters/cpplint.py {} \;
	@rm -f CPPLINT.cfg

style:
	cppcheck --enable=all --suppress=missingIncludeSystem ../../src

leaks:
	CK_FORK=no leaks --atExit -- ./s21_cat
