#include "s21_grep.h"

int main(int argc, char *argv[]) {
  s21_grep_programm(argc, argv);
  return 0;
}

void s21_grep(char *path, options config, char *template) {
  FILE *file = fopen(path, "r");
  if (file != NULL) {
    for (int sym = '0'; (sym = getc(file)) != EOF;) {
      char *line = calloc(256, 1);
      config.numberLine += 1;
      int length = 0;

      for (line[length] = '\0'; sym != EOF && sym != '\n'; sym = getc(file)) {
        line[length] = sym;
        line[length += 1] = '\0';
        if (length % 255 == 0) line = increase_length_str(line, length + 256);
      }

      print_main_data(line, &config, template, path);
      free(line);
    }
    printf_aux_data(config, path);
    fclose(file);
  } else if (config.s == 0) {
    fprintf(stderr, ERROR_01, path);
  }
}

void s21_grep_programm(int argc, char *argv[]) {
  if (argc > 1) {
    char *temp = NULL;
    options config = {0};
    for (int x = scan_options(argc, argv, &config, &temp); x < argc; x += 1)
      s21_grep(argv[x], config,
               temp);  // Цикл обработки файлов и применения функции grep
    if (temp != NULL) free(temp);
  }
}

int scan_options(int argc, char *argv[], options *config, char *template[]) {
  for (int sym = 0; (sym = getopt(argc, argv, "e:ivclnhsf:o")) != (-1);) {
    switch (sym) {
      case 'i':
        config->i = 1;
        break;
      case 'v':
        config->v = 1;
        break;
      case 'c':
        config->c = 1;
        break;
      case 'l':
        config->l = 1;
        break;
      case 'n':
        config->n = 1;
        break;
      case 'h':
        config->h = 1;
        break;
      case 's':
        config->s = 1;
        break;
      case 'o':
        config->o = 1;
        break;
      case 'e':
        set_config_flag_e(config, template, optarg);
        break;
      case 'f':
        set_config_flag_f(config, template, optarg);
        break;
    }
  }
  if ((config->e || config->f) == 0) {
    create_template(template, argv[optind]);
    optind += 1;
  }
  setup_config(config, argc);
  return optind;
}

void set_config_flag_f(options *config, char *template[], char *optarg) {
  FILE *file = fopen(optarg, "r");
  if (file != NULL) {
    for (int sym = '0'; (sym = getc(file)) != EOF;) {
      int length = 0;
      char *line = calloc(256, 1);

      for (line[length] = '\0'; sym != EOF && sym != '\n'; sym = getc(file)) {
        line[length] = sym;
        line[length += 1] = '\0';
        if (length % 255 == 0)
          line = (char *)increase_length_str(line, length + 256);
      }

      if (!(config->e || config->f))
        config->f = create_template(template, line);
      else
        add_template(template, line);
      free(line);
    }
    fclose(file);
  } else if (config->s == 0) {
    fprintf(stderr, ERROR_01, optarg);
  }
}

void set_config_flag_e(options *config, char *template[], char *optarg) {
  if (!(config->e || config->f))
    config->e = create_template(template, optarg);
  else
    add_template(template, optarg);
}

void printf_aux_data(options config, char *path) {
  if (config.c) {
    if (config.l) {
      config.countFiles > 1 ? printf("%s:1\n", path) : printf("1\n");
    } else {
      if (config.countFiles > 1) printf("%s:", path);
      printf("%i\n", config.countMatches);
    }
  }
  if (config.l && config.countMatches) printf("%s\n", path);
}

void print_main_data(char *line, options *config, char *template, char *path) {
  regex_t regex;
  if (regcomp(&regex, template, config->i ? REG_ICASE : REG_EXTENDED) == 0) {
    if (regexec(&regex, line, 0, NULL, 0) == config->v) {
      config->countMatches += 1;
      if ((config->c || config->l) == 0) {
        if (config->countFiles > 1 && !(config->h)) printf("%s:", path);
        if (config->n) printf("%i:", config->numberLine);
        if (!config->o)
          printf("%s\n", line);
        else
          print_config_o(regex, line, *config);
      }
    }
    regfree(&regex);
  }
}

void print_config_o(regex_t regex, char *line, options config) {
  while (regexec(&regex, line, 0, NULL, 0) == config.v) {
    char *aux = (char *)calloc(strlen(line) + 1, 1);
    strcpy(aux, line);
    // int end = strlen(line);
    while (regexec(&regex, aux, 0, NULL, 0) == config.v) {
    //   end--;
      aux[strlen(aux) - 1] = 0;
    }
    aux[strlen(aux)] = line[strlen(aux)];
    int start = 0;
    while (regexec(&regex, aux, 0, NULL, 0) == config.v && strlen(aux) > 0) {
      start++;
      int j = 0;
      while (aux[j] != 0) {
        aux[j] = aux[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(aux);
    while (i != 0) {
      aux[i] = aux[i - 1];
      i--;
    }
    aux[0] = line[start];
    printf("%s\n", aux);
    free(aux);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}

void setup_config(options *config, int argc) {
  if (config->o && (config->l || config->v || config->c)) config->o = 0;
  config->countFiles = argc - optind;
}

int create_template(char *str[], char *optarg) {
  *str = calloc(strlen(optarg) + 1, 1);
  if (*str) strcpy(*str, optarg);
  return str ? 1 : 0;
}

void add_template(char *str[], char *optarg) {
  *str = increase_length_str(*str, strlen(*str) + strlen(optarg) + 2);
  if (*str) strcat(strcat(*str, "|"), optarg);
}

void *increase_length_str(void *str, int size) {
  char *aux = realloc(str, size);
  return aux;
}
