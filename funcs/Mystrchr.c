#include "../Mystring.h"

char *Mystrchr(const char *str, int c) {
  for (;; ++str) {
    if (*str == c) {
      return (char *)str;
    }
    if (*str == '\0') {
      return MyNULL;
    }
  }
}