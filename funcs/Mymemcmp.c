#include "../Mystring.h"

int Mymemcmp(const void *str1, const void *str2, Mysize_t n) {
  unsigned char s1, s2;
  for (; n--; s1++, s2++) {
    s1 = *(unsigned char *)str1;
    s2 = *(unsigned char *)str2;
    if (s1 != s2) {
      return (s1 - s2);
    }
  }
  return 0;
}

// int Mymemcmp(const void *str1, const void *str2, Mysize_t n){
//     const unsigned char *s1 = (unsigned char*)str1;
//        const unsigned char *s2 = (unsigned char*)str2;
//     for(Mysize_t i = 0; i<n; i++){

//         if(s1[i]!=s2[i]){
//             return (s1[i]-s2[i]);
//         }
//     }
//     return 0;
// }