#include "modules.hh"
#include "version.hh"
#include <codecvt>
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
    help(argv[0]);
    exit(EXIT_FAILURE);
  }

  lines = 1;

  // Get terminal dimensions
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  unsigned short height = w.ws_row;
  width = w.ws_col;

  // index of arguments to display (not flags)
  int *display_args = (int *)malloc(sizeof(int) * argc);

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] != '-') {
      *display_args += 1;
      display_args[*display_args] = i;
      continue;
    }
    char ch = getoption(argv[i]);
    switch (ch) {
    case 's':
    case 'v':
    case 'o':
    case 'H':
    case 'W':
    case 'L':
      std::cout << "[" << ch << "] to be implemented";
      break;
    case 'V':
      std::cout << "Alinxt " << ALINXTVERSION << std::endl;
      exit(EXIT_SUCCESS);
    case 'h':
    case '?':
      help(argv[0]);
      exit(EXIT_SUCCESS);
    default:
      help(argv[0]);
      exit(EXIT_FAILURE);
    }
  }

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
