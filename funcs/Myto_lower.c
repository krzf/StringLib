#include "../Mystring.h"
void *Myto_lower(const char *str) {
  Mysize_t lenght = Mystrlen(str);
  char *res = malloc(lenght + 1);
  if (res == MyNULL) {
    return MyNULL;
  }
  for (Mysize_t i = 0; i < lenght; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      res[i] = str[i] + 32;
    } else {
      res[i] = str[i];
    }
  }
  res[lenght] = '\0';
  return (char *)res;
}
