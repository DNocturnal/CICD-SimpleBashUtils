#include "s21_cat.h"

int main(int argc, char **argv) {
  options *p = (options *)calloc(1, sizeof(options));
  s21_initial(p);
  print_flags(p, argc, argv);
  for (int i = 0; optind < argc; i++, optind++, p->n++) {
    snprintf(p->file[i], sizeof(p->file[i]), "%s", argv[optind]);
  }
  for (int i = 0; i < p->n; i++) {
    FILE *f = fopen(p->file[i], "r");
    if (f == NULL) {
      printf("file not exist\n");
    } else {
      s21_cat(f, p, i);
      fclose(f);
    }
  }
  free(p);
  return 0;
}

void s21_initial(options *ptr) {
  ptr->opt_b = 0;
  ptr->opt_e = 0;
  ptr->opt_s = 0;
  ptr->opt_t = 0;
  ptr->opt_n = 0;
  ptr->opt_E = 0;
  ptr->opt_T = 0;
  ptr->opt_v = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) ptr->file[i][j] = 0;
  }
  ptr->n = 0;
}

void print_flags(options *ptr, int argc, char **argv) {
  int c = 0;
  while ((c = getopt_long(argc, argv, "benstETv", long_opt, NULL)) != -1) {
    switch (c) {
      case 'b':
        ptr->opt_b = 1;
        break;
      case 'n':
        ptr->opt_n = 1;
        break;
      case 'e':
      case 'E':
        ptr->opt_e = 1;
        break;
      case 'v':
        ptr->opt_v = 1;
        break;
      case 't':
      case 'T':
        ptr->opt_t = 1;
        break;
      case 's':
        ptr->opt_s = 1;
        break;
      default:
        printf("Error: invalid flag");
    }
  }
}

void s21_cat(FILE *file, options *ptr, int i) {
  char c;
  char s = '\n';
  i = 1;
  while ((c = getc(file)) != EOF) {
    if (ptr->opt_e == 1) {
      ptr->opt_v = 1;
      if (c == '\n') printf("$");
    } else if (ptr->opt_E == 1) {
      ptr->opt_v = 0;
      if (c == '\n') printf("$");
    }
    if (ptr->opt_t == 1) {
      ptr->opt_v = 1;
      if (c == '\t') {
        printf("^I");
      } else {
        printf("%c", c);
      }
    } else if (ptr->opt_T == 1) {
      ptr->opt_v = 0;
      if (c == '\t') printf("^I");
    } else if (ptr->opt_b == 1) {
      if (s == '\n' && c != '\n') {
        printf("%6d\t", i++);
      }
      printf("%c", c);
    } else if (ptr->opt_n == 1) {
      if (s == '\n') {
        printf("%6d\t", i++);
      }
      printf("%c", c);
    } else if (ptr->opt_s == 1) {
      if (s == '\n' && c == '\n') {
        while (c == '\n') {
          c = getc(file);
        }
        printf("\n%c", c);
      } else {
        printf("%c", c);
      }
    } else if (c >= 0 && c < 32 && c != 9 && c != 10) {
      printf("^%c", c + 64);
    } else if (c == 127 && ptr->opt_E == 0 && ptr->opt_T == 0) {
      printf("^%c", c - 64);
    } else {
      printf("%c", c);
    }
    s = c;
  }
}
