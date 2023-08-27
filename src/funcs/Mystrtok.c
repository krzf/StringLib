#include "../Mystring.h"
// #include "Mystrspn.c"
// #include "Mystrcspn.c"

char *Mystrtok(char *str, const char *delim) {
  static char *lastToken = MyNULL;

  if (str == MyNULL) {
    str = lastToken;
  }

  str += Mystrspn(str, delim);

  if (*str == '\0') {
    lastToken = MyNULL;
    return MyNULL;
  }

  char *tokenEnd = str + Mystrcspn(str, delim);

  if (*tokenEnd == '\0') {
    lastToken = tokenEnd;
    return str;
  }

  *tokenEnd = '\0';
  lastToken = tokenEnd + 1;

  return str;
}
