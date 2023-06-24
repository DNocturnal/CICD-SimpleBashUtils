#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define short_opt = "benstETv";

typedef struct flags {
  int opt_b;
  int opt_e;
  int opt_n;
  int opt_s;
  int opt_t;
  int opt_v;
  int opt_E;
  int opt_T;
  int n;
  char file[20][20];
  int err;
} options;

const struct option long_opt[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {"number", no_argument, NULL, 'n'},
                                  {NULL, 0, NULL, 0}};

void s21_initial(options *prt);
void print_options(options *prt);
void s21_cat(FILE *file, options *ptr, int i);
void print_flags(options *ptr, int argc, char **argv);
void flag_squeeze(FILE *file, long size, char *buff);
#endif  // SRC_CAT_S21_CAT_H_
