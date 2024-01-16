#include <iostream>

extern unsigned int max_length;
extern unsigned short width;
extern unsigned int lines;
extern const bool is_ttyl;

/*
  Iterates through the string character by character.
  Calculates maximum line length.
*/
void scanarg(const char *str);

/*
  adds horizontal space from left
*/
inline void spacer();

/*
  display string
*/
inline void display(const char *str);

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
