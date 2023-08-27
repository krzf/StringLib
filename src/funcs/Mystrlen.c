#include "../Mystring.h"

Mysize_t Mystrlen(const char *str) {
  Mysize_t len = 0;
  for (; str[len];) {
    len += 1;
  }
  return len;
}