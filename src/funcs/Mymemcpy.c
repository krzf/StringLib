#include "../Mystring.h"

void *Mymemcpy(void *dest, const void *src, Mysize_t n) {
  char *dest1 = (char *)dest;
  char *src1 = (char *)src;
  for (Mysize_t i = 0; i < n; i++) {
    dest1[i] = src1[i];
  }
  return dest;
}
