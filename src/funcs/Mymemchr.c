#include "../Mystring.h"

void* Mymemchr(const void* str, int c, Mysize_t n) {
  const char* charStr = (const char*)str;
  for (Mysize_t i = 0; i < n; i++) {
    if (charStr[i] == c) {
      return (void*)&charStr[i];
    }
  }
  return MyNULL;
}