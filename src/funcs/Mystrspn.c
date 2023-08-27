#include "../Mystring.h"

Mysize_t Mystrspn(const char *str1, const char *str2) {
  Mysize_t i, j;
  for (i = 0; str1[i]; ++i) {  // str1[i] != '\0'
    for (j = 0; str2[j]; ++j) {
      if (str1[i] == str2[j]) {
        break;
      }
    }
    if (!str2[j]) {
      break;
    }
  }
  return i;
}