#include "modules.hh"
#include <cstdlib>
#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

unsigned int max_length = 0;
unsigned short width = 0;
unsigned int lines = 1;
const bool is_ttyl = isatty(STDOUT_FILENO);

int main(int argc, char **argv) {
  if (argc == 1) {
    std::cerr << "\033[31mError:\033[0m No arguments passed." << std::endl;
    return EXIT_FAILURE;
  }

  lines = 1;

  // Get terminal dimensions
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  unsigned short height = w.ws_row;
  width = w.ws_col;

  // Iterate through all arguments.
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      scanarg(argv[i]);
      lines++;
    }
  }

  // Top vertical padding
  if (height > lines && is_ttyl)
    for (int i = 0; i < (height - lines) / 2; i++)
      std::cout << "\n";
  spacer();

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-')
      display(argv[i]);
  }

  // Bottom vertical padding
  if (height > lines && is_ttyl)
    for (int i = 0; i < (height - lines) / 2; i++)
      std::cout << "\n";

  std::cout << "\n";
  return EXIT_SUCCESS;
}
