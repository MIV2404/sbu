#!/bin/sh

# Укажите путь к  программе
PATH_PROGRAM="./s21_cat"
# Укажите путь к утилите cat
CAT="/bin/cat"

# Папка с тестовыми файлами
TEST_DIR="../common/test_files"
# Папка для результатов  программы
OUTPUT_DIR="../common/test_cat/output"
# Папка для результатов утилиты cat
CAT_OUTPUT_DIR="../common/test_cat/cat_output"

# Создаем папки для результатов, если их нет
mkdir -p "$OUTPUT_DIR"
mkdir -p "$CAT_OUTPUT_DIR"

# Список файлов для тестирования
FILES_TO_TEST=("text.txt" "ascii_test.txt" "celebration.txt" "null.txt" "unknown_text.txt")

#FLGS="-t"

FLAGS_TO_TEST=("-b" "-e" "-n" "-s" "-t" "-b" 
"-e" "-n" "-s" "-t" "-be" "-bn" "-bs" "-bt"
 "-es" "-et" "-st" "-ben" "-bes" "-bet" "-bns"
"-bnt" "-bst" "-benst" "-seb")

for FLG in "${FLAGS_TO_TEST[@]}"
do

  for FILE in "${FILES_TO_TEST[@]}"
  do
    # Тестируем программу
    $PATH_PROGRAM $FLG "$TEST_DIR/$FILE" > "$OUTPUT_DIR/$FILE"

    # Тестируем утилиту cat
    $CAT $FLG "$TEST_DIR/$FILE" > "$CAT_OUTPUT_DIR/$FILE"

    # Сравниваем результаты
    diff -s "$OUTPUT_DIR/$FILE" "$CAT_OUTPUT_DIR/$FILE" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Тест для файла $FILE c флагом/флагами $FLG -> \033[32mпройден\033[0m"
    else
      echo "Тест для файла $FILE c флагом/флагами $FLG -> \033[31mНЕ ПРОЙДЕН!!!!!!!!!!!!\033[0m"
    fi
    rm -rf "$OUTPUT_DIR/$FILE"
    rm -rf "$CAT_OUTPUT_DIR/$FILE"

  done
done

for FILE in "${FILES_TO_TEST[@]}"
  do
    # Тестируем программу
    $PATH_PROGRAM --number-nonblank "$TEST_DIR/$FILE" > "$OUTPUT_DIR/$FILE"

    # Тестируем утилиту cat
    $CAT -b "$TEST_DIR/$FILE" > "$CAT_OUTPUT_DIR/$FILE"

    # Сравниваем результаты
    diff -s "$OUTPUT_DIR/$FILE" "$CAT_OUTPUT_DIR/$FILE" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Тест для файла $FILE c флагом/флагами --number-nonblank -> \033[32mпройден\033[0m"
    else
      echo "Тест для файла $FILE c флагом/флагами --number-nonblank -> \033[31mНЕ ПРОЙДЕН!!!!!!!!!!!!\033[0m"
    fi
    rm -rf "$OUTPUT_DIR/$FILE"
    rm -rf "$CAT_OUTPUT_DIR/$FILE"

  done

for FILE in "${FILES_TO_TEST[@]}"
  do
    # Тестируем программу
    $PATH_PROGRAM --number "$TEST_DIR/$FILE" > "$OUTPUT_DIR/$FILE"

    # Тестируем утилиту cat
    $CAT -n "$TEST_DIR/$FILE" > "$CAT_OUTPUT_DIR/$FILE"

    # Сравниваем результаты
    diff -s "$OUTPUT_DIR/$FILE" "$CAT_OUTPUT_DIR/$FILE" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Тест для файла $FILE c флагом/флагами --number -> \033[32mпройден\033[0m"
    else
      echo "Тест для файла $FILE c флагом/флагами --number -> \033[31mНЕ ПРОЙДЕН!!!!!!!!!!!!\033[0m"
    fi
    rm -rf "$OUTPUT_DIR/$FILE"
    rm -rf "$CAT_OUTPUT_DIR/$FILE"

  done

for FILE in "${FILES_TO_TEST[@]}"
  do
    # Тестируем программу
    $PATH_PROGRAM -Tv "$TEST_DIR/$FILE" > "$OUTPUT_DIR/$FILE"

    # Тестируем утилиту cat
    $CAT -t "$TEST_DIR/$FILE" > "$CAT_OUTPUT_DIR/$FILE"

    # Сравниваем результаты
    diff -s "$OUTPUT_DIR/$FILE" "$CAT_OUTPUT_DIR/$FILE" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Тест для файла $FILE c флагом/флагами -T -> \033[32mпройден\033[0m"
    else
      echo "Тест для файла $FILE c флагом/флагами -T -> \033[31mНЕ ПРОЙДЕН!!!!!!!!!!!!\033[0m"
    fi
    rm -rf "$OUTPUT_DIR/$FILE"
    rm -rf "$CAT_OUTPUT_DIR/$FILE"

  done

for FILE in "${FILES_TO_TEST[@]}"
  do
    # Тестируем программу
    $PATH_PROGRAM -Ev "$TEST_DIR/$FILE" > "$OUTPUT_DIR/$FILE"

    # Тестируем утилиту cat
    $CAT -e "$TEST_DIR/$FILE" > "$CAT_OUTPUT_DIR/$FILE"

    # Сравниваем результаты
    diff -s "$OUTPUT_DIR/$FILE" "$CAT_OUTPUT_DIR/$FILE" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Тест для файла $FILE c флагом/флагами -E -> \033[32mпройден\033[0m"
    else
      echo "Тест для файла $FILE c флагом/флагами -E -> \033[31mНЕ ПРОЙДЕН!!!!!!!!!!!!\033[0m"
    fi
    rm -rf "$OUTPUT_DIR/$FILE"
    rm -rf "$CAT_OUTPUT_DIR/$FILE"

  done  

for FILE in "${FILES_TO_TEST[@]}"
  do
    # Тестируем программу
    $PATH_PROGRAM --squeeze-blank "$TEST_DIR/$FILE" > "$OUTPUT_DIR/$FILE"

    # Тестируем утилиту cat
    $CAT -s "$TEST_DIR/$FILE" > "$CAT_OUTPUT_DIR/$FILE"

    # Сравниваем результаты
    diff -s "$OUTPUT_DIR/$FILE" "$CAT_OUTPUT_DIR/$FILE" > /dev/null
    if [ $? -eq 0 ]; then
      echo "Тест для файла $FILE c флагом/флагами --squeeze-blank -> \033[32mпройден\033[0m"
    else
      echo "Тест для файла $FILE c флагом/флагами --squeeze-blank -> \033[31mНЕ ПРОЙДЕН!!!!!!!!!!!!\033[0m"
    fi
    rm -rf "$OUTPUT_DIR/$FILE"
    rm -rf "$CAT_OUTPUT_DIR/$FILE"

  done