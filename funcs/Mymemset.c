#include "../Mystring.h"

void *Mymemset(void *str, int c, Mysize_t n) {
  unsigned char *p = str;
  unsigned char value = (unsigned char)c;

  for (Mysize_t i = 0; i < n; i++) {
    *p = value;
    p++;
  }
  return str;
}
