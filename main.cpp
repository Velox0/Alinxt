#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

unsigned int max_length = 0;
unsigned int lines = 1;

/*
    Accepts pointer to a string.
    Iterates through the string letter character by character.
    Until encounters '\0'.
*/
void scanarg(const char *str) {
  unsigned int str_length = 0;
  for (int i = 0; *(str + i) != '\0'; i++) {
    // count non-new-line characters
    if (*(str + i) != '\n')
      str_length++;
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

void spacer(int width) {
  for (int spacer = 0; spacer < (width - max_length) / 2; spacer++)
    std::cout << " ";
}

int main(int argc, char **argv) {
  if (argc == 1)
    return EXIT_FAILURE;

  lines += argc - 2;

  // Get terminal dimensions
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  unsigned short height = w.ws_row;
  unsigned short width = w.ws_col;

  // Iterate through all arguments.
  for (int i = 1; i < argc; i++) {
    scanarg(*(argv + i));
  }

  if (height > lines)
    for (int i = 0; i < (height - lines) / 2; i++)
      std::cout << '\n';
  spacer(width);

  if (width > max_length) {
    for (int i = 1; i < argc; i++) {
      for (int j = 0; *(*(argv + i) + j) != '\0'; j++) {
        std::cout << *(*(argv + i) + j);
        if (*(*(argv + i) + j) == '\n')
          spacer(width);
      }
      std::cout << std::endl;
      spacer(width);
    }
  }

  if (height > lines)
    for (int i = 2; i < (height - lines) / 2; i++)
      std::cout << '\n';

  std::cout << '\n';
  return EXIT_SUCCESS;
}
