#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 4096

typedef struct flags {
  int opt_v;
  int opt_c;
  int opt_i;
  int opt_n;
  int opt_l;
  int opt_h;
  int opt_f;
  int opt_o;
  int opt_e;
  int opt_s;
  int countFoundString;
  int countRemainingArguments;
  int currentFile;
  int current;
  int currentline;
} options;

void s21_print_flags(int argc, char** argv, options* f);
FILE* s21_open(char* argv, options* f, char* first_argv);
int s21_grep(FILE* file, char* template, char** argv, options* f);
void s21_f_n(char* buf, char* template, char* argv, options* f);
void s21_f_f(FILE* file, char* buf, char* template, char* argv, options* f);
void s21_f_e(char* buf, char* template, char* argv, options* f);
void s21_f_v(char* buf, char* template, char* argv, options* f);
void s21_f_o(char* buf, char* template, char* argv, options* f);
void s21_f_i(char* buf, regex_t* regex, char* argv, options* f);
void s21_f_s(options* f);
void s21_non_flags(options* f);

#endif  // SRC_GREP_S21_GREP_H_
