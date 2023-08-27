#include "../Mystring.h"
void *Mytrim(const char *src, const char *trim_chars) {
  if (src == MyNULL || trim_chars == MyNULL || *trim_chars == '\0') {
    return MyNULL;
  }

  Mysize_t src_len = Mystrlen(src);
  if (src_len == 0) {
    return MyNULL;
  }

  Mysize_t start_index = 0;
  Mysize_t end_index = src_len - 1;

  while (start_index <= end_index &&
         Mystrchr(trim_chars, src[start_index]) != MyNULL) {
    start_index++;
  }

  while (end_index > start_index &&
         Mystrchr(trim_chars, src[end_index]) != MyNULL) {
    end_index--;
  }

  Mysize_t trim_len = end_index - start_index + 1;
  char *trimmed_str = (char *)malloc((trim_len + 1) * sizeof(char));

  if (trimmed_str == MyNULL) {
    return MyNULL;
  }

  Mysize_t i;
  for (i = 0; i < trim_len; i++) {
    trimmed_str[i] = src[start_index + i];
  }

  trimmed_str[trim_len] = '\0';

  return trimmed_str;
}
