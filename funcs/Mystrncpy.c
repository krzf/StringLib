#include "../Mystring.h"

char *Mystrncpy(char *dest, const char *src, Mysize_t n) {
  Mysize_t i;

  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }

  for (; i < n; i++) {
    dest[i] = '\0';  // дополняем оставшуюся часть dest нулевыми символами
  }

  return dest;
}
