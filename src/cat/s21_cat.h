#ifndef SRC_CAT_S21_H_
#define SRC_CAT_S21_H_

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Options {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
  int T;
  int E;
  int ind;
};

static struct option long_options[] = {{"number-nonblank", 0, 0, 'b'},
                                       {"number", 0, 0, 'n'},
                                       {"squeeze-blank", 0, 0, 's'},
                                       {0, 0, 0, 0}};

int parser_flags(int argc, char *argv[], struct Options *options);
void printing_file(FILE *filename, struct Options *options);

#endif
