#ifndef MySTRING_H_
#define MySTRING_H_
#include <limits.h>  // for strerror test INT_MAX etc
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define MyNULL (void *)0
typedef long unsigned Mysize_t;

#define BUFF_SIZE 512

// arithm
Mysize_t Mystrlen(const char *str);
Mysize_t Mystrspn(const char *str, const char *sym);
Mysize_t Mystrcspn(const char *str1, const char *str2);
// COPYs
char *Mystrcpy(char *dest, const char *src);
char *Mystrncpy(char *dest, const char *src, Mysize_t n);
void *Mymemcpy(void *dest, const void *src, Mysize_t n);
void *Mymemset(void *str, int c, Mysize_t n);
// secondary
char *Mystrtok(char *str, const char *delim);
char *Mystrcat(char *dest, const char *src);
char *Mystrncat(char *dest, const char *src, Mysize_t n);

// ed
void *Mymemchr(const void *str, int c, Mysize_t n);
int Mymemcmp(const void *str1, const void *str2, Mysize_t n);
char *Mystrchr(const char *str, int c);
char *Mystrerror(int errnum);
char *Mystrpbrk(const char *str1, const char *str2);
char *Mystrrchr(const char *str, int c);
char *Mystrstr(const char *haystack, const char *needle);

void *Myto_upper(const char *str);
void *Myto_lower(const char *str);
int Mystrncmp(const char *str1, const char *str2, Mysize_t n);
void *Myinsert(const char *src, const char *str, Mysize_t start_index);
void *Mytrim(const char *src, const char *trim_chars);

// sprintf
// /////////////////////////////////////////////////////////////////////////////////////
typedef struct flags {
  char specifier;
  char length;
  int precision;
  int left_justify;
  int show_sign;
  int show_plus;
  int space;
  int width;
  int point;
  int flag_zero;
  int flag_sharp;
  int no_write;
} flags;

#define is_flag(ch)                                                   \
  ((ch) == '-') || ((ch) == '+') || ((ch) == ' ') || ((ch) == '#') || \
      ((ch) == '0')

#define is_digit(ch) ((ch) >= '0' && (ch) <= '9')

#define is_length(ch) ((ch) == 'h' || (ch) == 'l' || (ch) == 'L')

#define is_specifier(ch)                                                      \
  ((ch) == 'c' || (ch) == 'd' || (ch) == 'i' || (ch) == 'e' || (ch) == 'E' || \
   (ch) == 'f' || (ch) == 'g' || (ch) == 'G' || (ch) == 'o' || (ch) == 's' || \
   (ch) == 'u' || (ch) == 'x' || (ch) == 'X' || (ch) == 'p' || (ch) == 'n' || \
   (ch) == '%')

int Mysprintf(char *str, const char *format, ...);

// check
void parse_flags(flags *configs, const char *format);
char *parse_spec(char *str, Mysize_t *str_len, va_list *args, flags *configs);

// str
void make_str_flags(flags *configs, char *str);
void make_str_width(flags *configs, char *str);
void make_str_prec(flags *configs, char *str);
void move_str(char *str);
void reverse_writing(char *str);
int compare_round(flags *configs, long double number);
void make_mantissa(flags *configs, char *mantice, int notation);
void sharp_flag(flags *configs, char *str);
void delete_zero(flags *configs, char *str);

// specif
void format_char(char *str, va_list *args, flags *configs);
void format_di(char *str, va_list *args, flags *configs);
void format_s(char *str, va_list *args, flags *configs);
void format_u(char *str, va_list *args, flags *configs);
void format_f(char *str, va_list *args, flags *configs);
void format_gG(char *str, va_list *args, flags *configs);
void format_eE(char *str, va_list *args, flags *configs);
void format_n(Mysize_t const *str_len, va_list *args);
void format_p(char *str, va_list *args, flags *configs);
void format_xX(char *str, va_list *args, flags *configs);
void format_percentage(char *str, flags *configs);

void int_to_str(flags *configs, char *str, long double number);
char *str_to_int(int *number, const char *format, va_list *args);
void u_to_str(char *str, unsigned long long number, flags *configs);
void float_to_str(char *str, long double number, flags *configs);
void eE_to_str(char *str, long double number, flags *configs);
void gG_to_str(char *str, long double number, flags *configs);
void hlxX_to_str(char *str, unsigned long long number, flags *configs);
void ol_to_str(char *str, unsigned long long number, int pref);
void format_o(char *str, va_list *args, flags *configs);

void def_precision(flags *configs);

// sscanf
#define is_gef_valid(ch)                                                       \
  (is_digit(ch) || (ch) == '.' || (ch) == 'e' || (ch) == 'E' || (ch) == '+' || \
   (ch) == '-')


#endif