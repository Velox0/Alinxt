#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

static unsigned int max_length = 0;
static unsigned short width = 0;
static unsigned int lines = 1;
static const bool is_ttyl = isatty(STDOUT_FILENO);

/*
  Accepts pointer to a string.
  Iterates through the string character by character.
  Calculates maximum line length.
*/
void scanarg(const char *str) {
  unsigned int str_length = 0;
  for (int i = 0; *(str + i) != '\0'; i++) {
    // count non-new-line characters
    if (*(str + i) != '\n')
      str_length++;

    // count new-lines
    else if (str_length > max_length) {
      lines++;
      max_length = str_length;
      str_length = 0;
    } else {
      lines++;
      str_length = 0;
    }
  }

  if (str_length > max_length)
    max_length = str_length;
}

void spacer() {
  if (!is_ttyl || width < max_length)
    return;
  for (int spacer = 0; spacer < (width - max_length) / 2; spacer++)
    std::cout << " ";
}

void display(const char *str) {
  for (int j = 0; str[j] != '\0'; j++) {
    std::cout << str[j];
    if (str[j] == '\n')
      spacer();
  }
  std::cout << std::endl;
  spacer();
}

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cerr << "\033[31mError:\033[0m No arguments passed." << std::endl;
    return EXIT_FAILURE;
  }

  lines += argc - 2;

  // Get terminal dimensions
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  unsigned short height = w.ws_row;
  width = w.ws_col;

  // Iterate through all arguments.
  for (int i = 1; i < argc; i++) {
    scanarg(*(argv + i));
  }

  // Top vertical padding
  if (height > lines && is_ttyl)
    for (int i = 0; i < (height - lines) / 2; i++)
      std::cout << "\n";
  spacer();

  for (int i = 1; i < argc; i++) {
    display(argv[i]);
  }

  // Bottom vertical padding
  if (height > lines && is_ttyl)
    for (int i = 2; i < (height - lines) / 2; i++)
      std::cout << "\n";

  std::cout << "\n";
  return EXIT_SUCCESS;
}
