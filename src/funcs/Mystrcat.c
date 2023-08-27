#include "../Mystring.h"
char *Mystrcat(char *dest, const char *src) {
  int dest_len = Mystrlen(dest);
  int i = 0;

  for (; src[i]; i++) {
    dest[dest_len + i] = src[i];
  }

  dest[dest_len + i] = '\0';

  return dest;
}
//