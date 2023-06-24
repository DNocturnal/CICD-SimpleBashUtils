#!/bin/bash

cat -b test_cat.txt >> cat_result.txt
./s21_cat -b test_cat.txt >> s21_cat_result.txt
diff -s cat_result.txt s21_cat_result.txt
rm cat_result.txt s21_cat_result.txt

cat -e test_cat.txt >> cat_result.txt
./s21_cat -e test_cat.txt >> s21_cat_result.txt
diff -s cat_result.txt s21_cat_result.txt
rm cat_result.txt s21_cat_result.txt

cat -n test_cat.txt >> cat_result.txt
./s21_cat -n test_cat.txt >> s21_cat_result.txt
diff -s cat_result.txt s21_cat_result.txt
rm cat_result.txt s21_cat_result.txt

cat -t test_cat.txt >> cat_result.txt
./s21_cat -t test_cat.txt >> s21_cat_result.txt
diff -s cat_result.txt s21_cat_result.txt
rm cat_result.txt s21_cat_result.txt

cat -s test_cat.txt >> cat_result.txt
./s21_cat -s test_cat.txt >> s21_cat_result.txt
diff -s cat_result.txt s21_cat_result.txt
rm cat_result.txt s21_cat_result.txt

cat test_cat.txt >> cat_result.txt
./s21_cat test_cat.txt >> s21_cat_result.txt
diff -s cat_result.txt s21_cat_result.txt
rm cat_result.txt s21_cat_result.txt

