#include "../Mystring.h"

char *Mystrpbrk(const char *str1, const char *str2) {
  if (str1 == MyNULL || str2 == MyNULL) {
    return MyNULL;
  }
  const char *temp;
  while (*str1 != '\0') {
    temp = str2;

    while (*temp != '\0') {
      if (*str1 == *temp) {
        return (char *)str1;
      }
      temp++;
    }
    str1++;
  }
  return MyNULL;
}