#!/bin/bash

grep -n the test_grep.txt >> grep_result.txt
./s21_grep -n the test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -e the test_grep.txt >> grep_result.txt
./s21_grep -e the test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -h the test_grep.txt >> grep_result.txt
./s21_grep -h the test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -v the test_grep.txt >> grep_result.txt
./s21_grep -v the test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -o the test_grep.txt >> grep_result.txt
./s21_grep -o the test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -i the test_grep.txt >> grep_result.txt
./s21_grep -i the test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -s month test_grep.txt >> grep_result.txt
./s21_grep -s month test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep month test_grep.txt >> grep_result.txt
./s21_grep month test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -f test_grep.txt test_grep.txt >> grep_result.txt
./s21_grep -f test_grep.txt test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt

grep -l test_grep.txt test_grep.txt >> grep_result.txt
./s21_grep -l test_grep.txt test_grep.txt >> s21_grep_result.txt
diff -s grep_result.txt s21_grep_result.txt
rm grep_result.txt s21_grep_result.txt
