#include "../Mystring.h"
void *Myinsert(const char *src, const char *str, Mysize_t start_index) {
  if (src == MyNULL || Mystrlen(src) == 0 || *str == '\0' ||
      str == MyNULL || start_index > Mystrlen(src)) {
    return MyNULL;
  }
  Mysize_t src_len = Mystrlen(src);
  Mysize_t str_len = Mystrlen(str);
  Mysize_t new_len = src_len + str_len;
  char *res = (char *)malloc((new_len + 1) * sizeof(char));

  if (res == MyNULL) {
    return MyNULL;
  }
  Mysize_t i, j;
  for (i = 0; i < start_index; i++) {
    res[i] = src[i];
  }

  for (j = 0; j < str_len; j++) {
    res[i++] = str[j];
  }

  Mysize_t k = start_index;
  for (; k < src_len; k++) {
    res[i++] = src[k];
  }
  res[new_len] = '\0';
  return res;
  
}