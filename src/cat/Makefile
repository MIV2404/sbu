CC = gcc
FLAGS = -Wall -Werror -Wextra
FLAGS_FSAN = -Wall -Werror -Wextra -std=c11 -pedantic -fsanitize=address -fsanitize=leak
CLANGI = clang-format -i
CLANGN = clang-format -n

CAT = s21_cat

.PHONY: all clean rebuild s21_cat clangi clangn

all: s21_cat

s21_cat: s21_cat.h s21_cat.c
	$(CC) $(FLAGS) s21_cat.c s21_cat.h -o $(CAT)

test:
	sh test_script.sh

check:
	leaks --atExit -- ./s21_cat ../common/test_files/text.txt
	cppcheck --enable=all --suppress=missingIncludeSystem s21_cat.c


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

leaks:
	leaks -atExit -- ./$(CAT)

rebuild:
	make clean
	make all

clean:
	rm $(CAT)
