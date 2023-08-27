#include "../Mystring.h"

char *Mystrcpy(char *dest, const char *src) {
  for (int i = 0; src[i]; i++) {
    dest[i] = src[i];
  }

  dest[Mystrlen(src)] = '\0';

  return dest;
}