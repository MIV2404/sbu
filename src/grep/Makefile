CC = gcc
FLAGS = -Wall -Werror -Wextra
FLAGS_FSAN = -Wall -Werror -Wextra -std=c11 -pedantic -fsanitize=address -fsanitize=leak
CLANGI = clang-format -i
CLANGN = clang-format -n

GREP = s21_grep

.PHONY: all clean rebuild s21_grep

all: s21_grep

s21_grep: s21_grep.h s21_grep.c
	$(CC) $(FLAGS) s21_grep.c -o $(GREP)

clangi:
	@cp ../../materials/linters/.clang-format .
	@$(CLANGI) *.c
	@$(CLANGI) *.h
	@rm -rf .cilang-format

clangn:
	@cp ../../materials/linters/.clang-format .
	@$(CLANGN) *.c
	@$(CLANGN) *.h
	@rm -rf .cilang-format

cpp:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

test:
	sh test_script.sh

check:
	leaks --atExit -- ./s21_grep -n test ../common/test_files/text.txt
	cppcheck --enable=all --suppress=missingIncludeSystem s21_grep.c

rebuild:
	make clean
	make all

clean:
	rm $(GREP)
