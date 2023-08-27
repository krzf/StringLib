#include "../Mystring.h"
int Mystrncmp(const char *str1, const char *str2, Mysize_t n) {
  if (n == 0) {
    return 0;
  }
  do {
    if (*str1 != *str2++) {
      return (*(unsigned char *)str1 - *(unsigned char *)--str2);
    }
    if (*str1++ == 0) break;
  } while (--n != 0);
  return 0;
}