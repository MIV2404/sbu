
#include "s21_cat.h"

int main(int argc, char *argv[]) {
  int error;
  struct Options options = {0, 0, 0, 0, 0, 0, 0, 0, 1};
  error = parser_flags(argc, argv, &options);

  if (!error) {
    for (int i = options.ind; i < argc; i++) {
      FILE *filename;
      char *name_file = argv[i];
      filename = fopen(name_file, "r");
      if (!filename) {
        printf("s21_cat: %s: No such file or directory\n", name_file);
      } else {
        printing_file(filename, &options);
        fclose(filename);
      }
    }
  } else {
    printf("s21_cat: illegal option \n");
  }

  return 0;
}

int parser_flags(int argc, char *argv[], struct Options *options) {
  int opt;
  int error = 0;
  const char *valid_options = "benstvTE";
  opterr = 0;

  while ((opt = getopt_long(argc, argv, valid_options, long_options, NULL)) !=
         -1) {
    options->ind = optind;
    if (opt == 'b')
      options->b = 1;
    else if (opt == 'e') {
      options->e = 1;
      options->v = 1;
    } else if (opt == 'n')
      options->n = 1;
    else if (opt == 's')
      options->s = 1;
    else if (opt == 't') {
      options->t = 1;
      options->v = 1;
    } else if (opt == 'T')
      options->t = 1;
    else if (opt == 'E')
      options->e = 1;
    else if (opt == 'v')
      options->v = 1;
    else
      error = 1;
  }

  if (options->b == 1) options->n = 0;
  return error;
}

void printing_file(FILE *filename, struct Options *options) {
  int c, i = 0;
  char prev = '\n', prev_prev = ' ';

  while ((c = fgetc(filename)) != EOF) {
    if (options->n == 1 && prev == '\n') {
      ++i;
      printf("%6d\t", i);
    }
    if (options->b == 1 && prev == '\n' && c != '\n') {
      i++;
      printf("%6d\t", i);
    }
    if (options->s == 1 && c == '\n' && prev == '\n' && prev_prev == '\n')
      continue;
    if (options->e == 1 && c == '\n') printf("$");
    if (options->t == 1 && c == '\t') {
      printf("^");
      c = 'I';
    }
    if (options->v == 1 && c >= 0 && c <= 31 && c != '\n' && c != '\t') {
      printf("^");
      c += 64;
    } else if (options->v == 1 && c == 127) {
      printf("^");
      c = '?';
    } else if (options->v == 1 && c >= 127 && c < 160) {
      printf("M-^");
      c += 192;
    }

    printf("%c", c);
    prev_prev = prev;
    prev = c;
  }
}
