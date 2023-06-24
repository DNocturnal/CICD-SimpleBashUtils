#include "s21_grep.h"

FILE* s21_open(char* argv, options* f, char* first_argv) {
  FILE* file;
  if ((file = fopen(argv, "r")) == NULL && !f->opt_s) {
    fprintf(stderr, "%s: %s No such file or directory\n", first_argv, argv);
  }
  return file;
}

void s21_print_flags(int argc, char** argv, options* f) {
  int opt;
  while ((opt = getopt(argc, argv, "vcinlhfoes")) != -1) {
    switch (opt) {
      case 'v':
        f->opt_v++;
        break;
      case 'c':
        f->opt_c++;
        break;
      case 'i':
        f->opt_i++;
        break;
      case 'n':
        f->opt_n++;
        break;
      case 'l':
        f->opt_l++;
        break;
      case 'h':
        f->opt_h++;
        break;
      case 'f':
        f->opt_f++;
        break;
      case 'o':
        f->opt_o++;
        break;
      case 'e':
        f->opt_e++;
        break;
      case 's':
        f->opt_s++;
        break;
    }
  }
  f->countRemainingArguments = argc - optind - 1;
  f->currentFile = optind + 1;
  f->current = optind;
}

void s21_f_n(char* buf, char* template, char* argv, options* f) {
  if (strstr(buf, template)) {
    if (f->countRemainingArguments == 1)
      printf("%d:%s", f->currentline, buf);
    else
      printf("%s:%d:%s", argv, f->currentline, buf);
  }
}

void s21_f_f(FILE* fi, char* buf, char* template, char* argv, options* f) {
  if (!fi) f->opt_f = 0;
  if (f->opt_f) {
    template = (fgets(template, SIZE, fi));
    if (strstr(buf, template)) {
      if (f->countRemainingArguments != 1)
        printf("%s:%s", argv, buf);
      else
        printf("%s", buf);
    }
    fclose(fi);
  }
}

void s21_f_e(char* buf, char* template, char* argv, options* f) {
  if (strstr(buf, template)) {
    if (f->countRemainingArguments != 1)
      printf("%s:%s", argv, buf);
    else
      printf("%s", buf);
  }
}

void s21_f_v(char* buf, char* template, char* argv, options* f) {
  if (!strstr(buf, template)) {
    if (f->countRemainingArguments != 1)
      printf("%s:%s", argv, buf);
    else
      printf("%s", buf);
  }
}

void s21_f_o(char* buf, char* template, char* argv, options* f) {
  char* temp;
  while ((temp = strstr(buf, template))) {
    buf = (temp + 1);
    if (f->countRemainingArguments != 1) {
      printf("%s:%s\n", argv, template);
    } else {
      printf("%s\n", template);
    }
  }
}

void s21_f_i(char* buf, regex_t* regex, char* argv, options* f) {
  int c = regexec(regex, buf, 0, NULL, 0);
  if (c == 0 && !f->opt_v) {
    if (f->countRemainingArguments != 1 && !f->opt_h) {
      if (f->opt_n)
        printf("%s:%d:%s", argv, f->currentline, buf);
      else
        printf("%s:%s", argv, buf);
    } else {
      if (f->opt_n)
        printf("%d:%s", f->currentline, buf);
      else
        printf("%s", buf);
    }
  } else if (c != 0 && f->opt_v) {
    if (f->countRemainingArguments != 1)
      printf("%s:%s", argv, buf);
    else
      printf("%s", buf);
  }
}

void s21_non_flags(options* f) {
  if (f->opt_e == 0 && f->opt_i == 0 && f->opt_v == 0 && f->opt_c == 0 &&
      f->opt_l == 0 && f->opt_n == 0 && f->opt_h == 0 && f->opt_s == 0 &&
      f->opt_f == 0 && f->opt_o == 0)
    f->opt_e = 1;
}

void s21_f_s(options* f) {
  if (f->opt_e == 0 && f->opt_i == 0 && f->opt_v == 0 && f->opt_c == 0 &&
      f->opt_l == 0 && f->opt_n == 0 && f->opt_h == 0 && f->opt_s == 1 &&
      f->opt_f == 0 && f->opt_o == 0)
    f->opt_e = 1;
}

int main(int argc, char** argv) {
  options f = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  s21_print_flags(argc, argv, &f);
  s21_non_flags(&f);
  s21_f_s(&f);
  char template[SIZE];
  if (!f.opt_f) snprintf(template, SIZE, "%s", argv[f.current]);
  while (f.currentFile < argc) {
    FILE* file = s21_open(argv[f.currentFile], &f, argv[0]);
    if (file) {
      f.countFoundString =
          f.countFoundString + s21_grep(file, template, argv, &f);
      fclose(file);
      if (f.opt_c && f.countRemainingArguments > 1)
        printf("%s:%d\n", argv[f.currentFile], f.countFoundString);
      if (f.opt_c && f.countRemainingArguments == 1)
        printf("%d\n", f.countFoundString);
      f.countFoundString = 0;
      f.currentline = 0;
    }
    f.currentFile++;
  }
  return 0;
}

int s21_grep(FILE* file, char* template, char** argv, options* f) {
  char buf[SIZE];
  regex_t regex;
  int regflag = 0;
  int foundpattern = 0;
  if (f->opt_i) regflag = REG_ICASE;
  regcomp(&regex, argv[f->current], regflag);
  while (fgets(buf, SIZE, file)) {
    f->currentline++;
    if (f->opt_i) {
      s21_f_i(buf, &regex, argv[f->currentFile], f);
    } else if (f->opt_e) {
      s21_f_e(buf, template, argv[f->currentFile], f);
    } else if (f->opt_c) {
      if (strstr(buf, template)) f->countFoundString++;
    } else if (f->opt_l) {
      if (strstr(buf, template)) foundpattern = 1;
    } else if (f->opt_v) {
      s21_f_v(buf, template, argv[f->currentFile], f);
    } else if (f->opt_n) {
      s21_f_n(buf, template, argv[f->currentFile], f);
    } else if (f->opt_h) {
      if (strstr(buf, template)) printf("%s", buf);
    } else if (f->opt_o) {
      s21_f_o(buf, template, argv[f->currentFile], f);
    } else if (f->opt_f) {
      FILE* fi = s21_open(argv[f->current], f, argv[0]);
      s21_f_f(fi, buf, template, argv[f->currentFile], f);
    }
  }
  regfree(&regex);
  if (foundpattern) printf("%s\n", argv[f->currentFile]);
  return f->countFoundString;
}
