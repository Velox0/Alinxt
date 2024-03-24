#include <iostream>
#include <ostream>
#include <string>

extern unsigned int max_length;
extern unsigned short width;
extern unsigned int lines;
extern const bool is_ttyl;

struct error {
  enum type { BAD_OPTION, NO_VALUE, INVALID_VALUE };
  char option;
} err;

/*!
 * @function    scanarg
 * @abstract    calculates newlines and max line length
 * @param       str       pointer to string
 * @result      updates var lines and var max_length
 */
void scanarg(const char *str);

/*!
 * @function    spacer
 * @abstract    prints required spaces to center text
                from the left
 */
inline void spacer();

/*!
 * @function    display
 * @abstract    displays string character by character
 * @param       str       pointer to string\
 */
inline void display(const char *str);

/*!
 * @function    getoption
 * @abstract    option handler
 * @param       ch       pointer to option string
 * @result      returns appropriate character to match the
                long or short option
 */
char getoption(char *ch);

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

inline void spacer() {
  if (!is_ttyl || width < max_length)
    return;
  for (int spacer = 0; spacer < (width - max_length) / 2; spacer++)
    std::cout << " ";
}

inline void display(const char *str) {
  for (int j = 0; str[j] != '\0'; j++) {
    std::cout << str[j];
    if (str[j] == '\n')
      spacer();
  }
  std::cout << std::endl;
  spacer();
}

char getoption(char *ch) {
  if (ch[1] != '-')
    return ch[1];
  std::string options[] = {
      "stdin",  "vertical-only", "horizontal-only", "trim-top", "trim-bottom",
      "height", "width",         "linewidth",       "version",  "help"};

  char shortoptions[] = "svotbHWLVh";

  for (int i = 0; i < 10; i++) {
    for (int j = 2; ch[j]; j++) {
      if (ch[j] != options[i][j - 2])
        break;
      if (!ch[j + 1] && !options[i][j - 1])
        return shortoptions[i];
    }
  }
  return '\0';
}

void help(char arg[]) {
  std::cout << "Usage: " << arg << " [OPTION]"
            << " text" << std::endl
            << std::endl;
  std::cout << "  -h, --help             \tprint this help message\n"
            << "  -s, --stdin            \tinput from standard input\n"
            << "  -v, --vertical-only    \tonly center vertically\n"
            << "  -o, --horizontal-only  \tonly center horizontally\n"
            << "  -t, --trim-top    <num>\tremove blank new-lines from top\n"
            << "  -b, --trim-bottom <num>\tremove blank new-lines from bottom\n"
            << "  -H, --height      <num>\texplicitly set tty height\n"
            << "  -W, --width       <num>\texplicitly set tty width\n"
            << "  -L, --linewidth   <num>\texplicitly set max-line length\n"
            << "  -V, --version          \tget program version info\n"
            << std::endl;
}
