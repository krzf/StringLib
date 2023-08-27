#include "../Mystring.h"

char *Mystrrchr(const char *str, int c) {
  if (str == MyNULL) {
    return MyNULL;
  }
  if ((char)c == '\0') {
    return "";
  }
  char *p = MyNULL;
  while (*str != '\0') {
    if (*str == (char)c) {
      p = (char *)str;
    }
    str++;
  }
  return p;
}
