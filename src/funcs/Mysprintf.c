#include "../Mystring.h"

int Mysprintf(char *str, const char *format, ...)

{
  va_list args = {0};
  va_start(args, format);
  flags configs = {0};
  Mysize_t i = 0;
  str = Mystrcpy(str, "");
  while (*format) {
    configs.precision = -1;
    configs.flag_sharp = configs.show_sign = configs.flag_zero =
        configs.show_plus = configs.left_justify = configs.space =
            configs.width = configs.point = configs.specifier = configs.length =
                0;
    switch (*format) {
      case '%':
        format++;
        if (is_flag(*format)) {
          while (is_flag(*format)) {
            parse_flags(&configs, format++);
          }
        }
        if (is_digit(*format) || *format == '*') {
          format = str_to_int(&configs.width, format++, &args);
          if (configs.width < 0) {
            configs.left_justify = 1;
            configs.width *= -1;
          }
        }
        if (*format == '.') {
          configs.point = 1;
          configs.precision = 0;
          format++;
          if (is_digit(*format) || *format == '*') {
            format = str_to_int(&configs.precision, format++, &args);
          } else {
            configs.precision = -1;
          }
        }
        if (is_length(*format)) {
          while (is_length(*format)) {
            configs.length = *(format++);
          }
        }

        if (is_specifier(*format)) {
          configs.specifier = *(format++);
        }
        def_precision(&configs);
        str = parse_spec(str, &i, &args, &configs);
        break;
      default:
        str[i++] = *(format++);
        str[i] = '\0';
        break;
    }
  }
  va_end(args);
  return (int)Mystrlen(str);
}
///////////////////////////////////////////////////////////

///////////////////////////////
void def_precision(flags *configs) {
  if (configs->point && configs->precision <= 0) {
    configs->precision = 0;
  }
  if (!configs->point && Mystrchr("eEfgG", configs->specifier)) {
    configs->precision = 6;
  }
}

void parse_flags(flags *configs, const char *format) {
  switch (*format) {
    case '-':
      configs->left_justify = 1;
      break;
    case '+':
      configs->show_plus = 1;
      break;
    case ' ':
      configs->space = 1;
      break;
    case '#':
      configs->flag_sharp = 1;
      break;
    case '0':
      configs->flag_zero = 1;
      break;
  }
}

char *parse_spec(char *str, Mysize_t *str_len, va_list *args,
                 flags *configs) {
  char *tmp_str = MyNULL;
  tmp_str = calloc(1024, sizeof(char));
  if (tmp_str != MyNULL) {
    switch (configs->specifier) {
      case 'c':
        format_char(tmp_str, args, configs);
        break;
      case 'd':
      case 'i':
        format_di(tmp_str, args, configs);
        break;
      case 'u':
        format_u(tmp_str, args, configs);

        break;
      case 'f':
        format_f(tmp_str, args, configs);
        break;
      case 'g':
      case 'G':
        format_gG(tmp_str, args, configs);
        break;
      case 'e':
      case 'E':
        format_eE(tmp_str, args, configs);
        break;
      case 'n':
        format_n(str_len, args);
        break;
      case 'o':
        format_o(tmp_str, args, configs);
        break;
      case 'p':
        format_p(tmp_str, args, configs);
        break;
      case 'x':
      case 'X':
        format_xX(tmp_str, args, configs);
        break;
      case 's':
        format_s(tmp_str, args, configs);
        break;
      case '%':
        format_percentage(tmp_str, configs);

        break;
    }
    Mystrcat(str, tmp_str);
    free(tmp_str);
    *str_len = Mystrlen(str);
  }
  return str;
}

// Specifier funcs

// char
void format_char(char *str, va_list *args, flags *configs) {
  str[0] = va_arg(*args, int);
  str[1] = '\0';
  make_str_flags(configs, str);
  make_str_width(configs, str);
}

void format_di(char *str, va_list *args, flags *configs) {
  long int ld_number = 0;
  short int sd_number = 0;
  int number = 0;

  switch (configs->length) {
    case 'h':
      sd_number = (short int)va_arg(*args, int);
      int_to_str(configs, str, sd_number);
      break;
    case 'l':
      ld_number = (long int)va_arg(*args, long int);
      int_to_str(configs, str, ld_number);
      break;
    default:
      number = va_arg(*args, int);
      int_to_str(configs, str, number);
      break;
  }
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}
void format_s(char *str, va_list *args, flags *configs) {
  char *string = MyNULL;
  string = va_arg(*args, char *);
  if (configs->precision > -1)
    Mystrncat(str, string, configs->precision);
  else
    Mystrcat(str, string);
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}

void format_u(char *str, va_list *args, flags *configs) {
  unsigned short us_number = 0;
  unsigned long ul_number = 0;
  unsigned int u_number = 0;

  switch (configs->length) {
    case 'h':
      us_number = (unsigned short)va_arg(*args, unsigned int);
      u_to_str(str, us_number, configs);
      break;
    case 'l':
      ul_number = (unsigned long)va_arg(*args, unsigned long);
      u_to_str(str, ul_number, configs);
      break;
    default:
      u_number = (unsigned int)va_arg(*args, unsigned int);
      u_to_str(str, u_number, configs);
      break;
  }
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}

void format_f(char *str, va_list *args, flags *configs) {
  long double l_number = 0;
  double d_number = 0;

  switch (configs->length) {
    case 'L':
      l_number = va_arg(*args, long double);
      float_to_str(str, l_number, configs);
      break;
    case 'l':
    default:
      d_number = va_arg(*args, double);
      float_to_str(str, d_number, configs);
      break;
  }
  make_str_flags(configs, str);
  make_str_width(configs, str);
}
void format_gG(char *str, va_list *args, flags *configs) {
  long double l_number = 0;
  double number = 0;

  switch (configs->length) {
    case 'L':
      l_number = va_arg(*args, long double);
      gG_to_str(str, l_number, configs);
      break;
    case 'l':
    default:
      number = va_arg(*args, double);
      gG_to_str(str, number, configs);
      break;
  }
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}
void format_eE(char *str, va_list *args, flags *configs) {
  long double l_number = 0;
  double number = 0;
  switch (configs->length) {
    case 'L':
      l_number = va_arg(*args, long double);
      eE_to_str(str, l_number, configs);
      break;
    default:
      number = va_arg(*args, double);
      eE_to_str(str, number, configs);
      break;
  }
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}
void format_n(Mysize_t const *str_len, va_list *args) {
  int *p = va_arg(*args, int *);
  *p = (int)*str_len;
}

void format_p(char *str, va_list *args, flags *configs) {
  int width;
  if (configs->width < 15) {
    width = 15;
  } else {
    width = configs->width;
  }
  char *start = MyNULL;
  start = str;
  int *p = va_arg(*args, int *);
  char buf[4] = "x0";
  if (p == MyNULL) {
    Mystrcpy(buf, "0x0");
  }
  for (int *j = p, k = 0; j && k < width;
       j = (void *)(((Mysize_t)j) >> 4), k++) {
    unsigned int dig = ((Mysize_t)j) % 0x10;
    if (dig < 10)
      *(start++) = (char)('0' + dig);
    else
      *(start++) = (char)('a' + (dig - 10));
  }
  *start = '\0';
  Mystrcat(str, buf);
  reverse_writing(str);
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}

void format_xX(char *str, va_list *args, flags *configs) {
  unsigned long int ld_number = 0;
  unsigned short int sd_number = 0;
  unsigned int number = 0;

  switch (configs->length) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*args, unsigned int);
      hlxX_to_str(str, sd_number, configs);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*args, unsigned long int);
      hlxX_to_str(str, ld_number, configs);
      break;
    default:
      number = (unsigned int)va_arg(*args, unsigned int);
      hlxX_to_str(str, number, configs);
      break;
  }
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}
void format_o(char *str, va_list *args, flags *configs) {
  unsigned long int ld_number = 0;
  unsigned short int sd_number = 0;
  unsigned int number = 0;

  switch (configs->length) {
    case 'h':
      sd_number = (unsigned short int)va_arg(*args, unsigned int);
      ol_to_str(str, sd_number, configs->flag_sharp);
      break;
    case 'l':
      ld_number = (unsigned long int)va_arg(*args, unsigned long int);
      ol_to_str(str, ld_number, configs->flag_sharp);
      break;
    default:
      number = va_arg(*args, unsigned int);
      ol_to_str(str, number, configs->flag_sharp);
      break;
  }
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}

void gG_to_str(char *str, long double number, flags *configs) {
  if (number < 0) {
    configs->show_sign = -1;
  } else {
    configs->show_sign = 1;
  }
  number *= configs->show_sign;
  int local_sign = configs->show_sign;
  if ((number / pow(10, configs->precision)) > 1 ||
      ((number * (pow(10, 4))) < 1 && (number * (pow(10, 21))) >= 1)) {
    if (number < 1 && configs->precision <= 0) {
      configs->precision = 4;
    } else {
      --configs->precision;
    }
    eE_to_str(str, number, configs);
  } else {
    configs->precision > 0 ? 1 : ++configs->precision;
    float_to_str(str, number, configs);
    delete_zero(configs, str);
  }
  configs->show_sign = local_sign;
}

void delete_zero(flags *configs, char *str) {
  int pos = (int)Mystrlen(str) - 1;
  if (pos > 0) {
    while (str[pos] == '0') {
      if (!configs->flag_sharp ||
          (configs->flag_sharp && pos > configs->precision)) {
        str[pos] = '\0';
        pos -= 1;
      }
    }
    if (!configs->flag_sharp && str[pos] == '.') {
      str[pos] = '\0';
    }
  }
}
void hlxX_to_str(char *str, unsigned long long number, flags *configs) {
  char *point = MyNULL;
  int flag = 1, shift = 0;
  point = str;
  if (configs->specifier == 'x') {
    shift = 32;
  } else {
    shift = 0;
  }

  while (flag) {
    unsigned int digit;
    if (number > 15) {
      digit = number % 16;
      number = (number - digit) / 16;
    } else {
      digit = number;
      flag = 0;
    }
    if (digit < 10)
      *(point++) = (char)(digit + '0');
    else
      *(point++) = (char)(digit + 'A' + shift - 10);
  }
  *point = '\0';
  if (number == 0) configs->flag_sharp = 0;
  reverse_writing(str);
}

void ol_to_str(char *str, unsigned long long number, int pref) {
  char *point = MyNULL;
  int flag = 1;

  point = str;

  while (flag) {
    unsigned int digit;
    if (number > 7) {
      digit = number % 8;
      number = (number - digit) / 8;
    } else {
      digit = number;
      flag = 0;
    }
    *(point++) = (char)(digit + '0');
  }

  if (pref == 1) *(point++) = '0';
  *point = '\0';
  reverse_writing(str);
}

void int_to_str(flags *configs, char *str, long double number) {
  char *point = MyNULL;
  int flag = 1;
  if (number < 0) {
    configs->show_sign = -1;
  } else {
    configs->show_sign = 1;
  }
  number *= configs->show_sign;
  point = str;
  if (configs->specifier != 'n') {
    while (flag) {
      int digit = 0;
      if (number >= 10) {
        digit = (int)fmod(number, 10);
        number = (number - digit) / 10;
      } else {
        digit = (int)number;
        flag = 0;
      }
      *(point++) = (char)(digit + '0');
    }
    if (Mystrchr("dioxX", configs->specifier) && configs->precision == 0 &&
        number == 0 && configs->point)
      str[0] = '\0';
    *point = '\0';
    reverse_writing(str);
  }
}

char *str_to_int(int *number, const char *format, va_list *args) {
  char s[128] = {0};
  char *num = NULL;
  int count = 0;
  while (is_digit(*format)) {
    s[count++] = *(format)++;
  }
  num = s;
  while (count > 0) {
    *number += ((*(num)++) - '0') * pow(10, --count);
  }
  if (*format == '*') {
    *number = va_arg(*args, int);
    format++;
  }
  return (char *)format;
}

void u_to_str(char *str, unsigned long long number, flags *configs) {
  char *point = MyNULL;
  int flag = 1;

  point = str;

  while (flag) {
    int digit = 0;
    if (number >= 10) {
      digit = (int)fmod(number, 10);
      number = (number - digit) / 10;
    } else {
      digit = (int)number;
      flag = 0;
    }
    *(point++) = (char)(digit + '0');
  }
  if (configs->precision == 0 && number == 0 && configs->point) str[0] = '\0';
  *point = '\0';
  reverse_writing(str);
}

void float_to_str(char *str, long double number, flags *configs) {
  if (number < 0) {
    configs->show_sign = -1;
  } else {
    configs->show_sign = 1;
  }
  number *= configs->show_sign;
  int local_sign = configs->show_sign;
  if (configs->precision <= 0) {
    int_to_str(configs, str, roundl(number));
  } else {
    long double left = 0, right = 0;
    int pos = 0;
    char result[256] = {0};
    right = modfl(number, &left);
    if (Mystrchr("gG", configs->specifier) && configs->precision == 1 &&
        right >= 0.5) {
      left++;
    }
    int_to_str(configs, str, roundl(left));
    Mystrcat(str, ".");
    int local_precision = configs->precision;
    if (Mystrchr("gG", configs->specifier)) {
      if (left >= 1) {
        local_precision = configs->precision - (int)Mystrlen(str) + 1 +
                          ((int)roundl(number) == 0);
      } else if (right * pow(10, local_precision) < 1) {
        local_precision = 4;
      }
    }
    for (int i = 0; i < local_precision; i++) right *= 10;
    int_to_str(configs, result, roundl(right));
    pos = (int)Mystrlen(result);
    for (int i = 0; pos < local_precision; i++, pos++) {
      move_str(result);
      result[i] = '0';
    }
    if (Mystrchr("gG", configs->specifier) && (int)roundl(number) != 0) {
      result[configs->precision - (int)Mystrlen(str) + 1] = '\0';
    }
    Mystrcat(str, result);
  }
  configs->show_sign = local_sign;
}

void eE_to_str(char *str, long double number, flags *configs) {
  if (number < 0) {
    configs->show_sign = -1;
  } else {
    configs->show_sign = 1;
  }
  int notation = 0, local_sign = configs->show_sign;
  number *= configs->show_sign;
  if (number < 1) {
    while (number < 1 && notation-- > -42) {
      number *= 10;
    }
    number < 1 ? (notation = number = 0) : 1;
    if (compare_round(configs, number)) {
      if (configs->precision >= 0) {
        --configs->precision;
      }
      notation++;
    }
    if (Mystrchr("gG", configs->specifier)) delete_zero(configs, str);
    make_mantissa(configs, &str[Mystrlen(str)], notation);
  } else {
    while (number >= 10) {
      notation++;
      number /= 10;
    }
    if (compare_round(configs, number)) {  // compare round
      if (configs->precision >= 0) {
        --configs->precision;
      }
      notation++;
    }
  }
  number = roundl(number * pow(10, configs->precision));
  int_to_str(configs, str, number);
  if (configs->precision > 0) {
    move_str(&str[1]);
    str[1] = '.';
    for (int i = (int)Mystrlen(str); i < 2 + configs->precision; i++) {
      str[i] = '0';
    }
  }
  if (Mystrchr("gG", configs->specifier)) delete_zero(configs, str);
  make_mantissa(configs, &str[Mystrlen(str)], notation);  // make mantissa
  configs->show_sign = local_sign;
}

int compare_round(flags *configs, long double number) {
  char compare_str[128] = {'\0'};
  int length = 0, result = 0;
  number *= pow(10, configs->precision);
  int_to_str(configs, compare_str, number);
  length = Mystrlen(compare_str);
  number = roundl(number);
  int_to_str(configs, compare_str, number);
  if (length < (int)Mystrlen(compare_str)) {
    result = 1;
  }
  return result;
}

void reverse_writing(char *str) {
  char c = 0;
  Mysize_t length = Mystrlen(str);
  for (Mysize_t i = 0; i < length / 2; i++) {
    c = str[i];
    str[i] = str[length - 1 - i];
    str[length - 1 - i] = c;
  }
}

void make_mantissa(flags *configs, char *mantice, int notation) {
  int start_pos = 0;
  if (configs->flag_sharp && configs->precision <= 0) {
    mantice[start_pos++] = '.';
  }
  if (Mystrchr("eg", configs->specifier)) {
    mantice[start_pos] = 'e';
  } else {
    mantice[start_pos] = 'E';
  }
  start_pos++;  //
  if (notation >= 0) {
    mantice[start_pos] = '+';
  } else {
    mantice[start_pos] = '-';
  }
  start_pos++;  //
  if (abs(notation) < 10) {
    mantice[start_pos++] = '0';
    int_to_str(configs, &mantice[start_pos], abs(notation));
  } else {
    int_to_str(configs, &mantice[start_pos], abs(notation));
  }
}

void make_str_flags(flags *configs, char *str) {
  int pos = 0;
  if (!Mystrchr("cuo%%", configs->specifier)) {  //???? \% %% %????
    if (configs->specifier != 'x' && configs->specifier != 'X') {
      if (configs->show_sign < 0) {
        move_str(str);
        str[pos++] = '-';
        configs->show_sign = 0;
      }
      if (configs->show_plus && configs->show_sign != 0) {
        move_str(str);
        if (configs->show_sign > 0) {
          str[pos] = '+';
        } else {
          str[pos] = '-';
        }
        configs->show_sign = 0;
      }
      if (configs->space && configs->show_sign != 0) {
        move_str(str);
        if (configs->show_sign > 0) {
          str[pos] = ' ';
        } else {
          str[pos] = '-';
        }
        configs->show_sign = 0;
      }
    }
    if (configs->flag_sharp) {  // additional flags
      sharp_flag(configs, str);
    }
  }
  if (configs->left_justify) {
    pos = (int)Mystrlen(str);
    while (pos < configs->width) {
      str[pos++] = ' ';
    }
  }
}

void sharp_flag(flags *configs, char *str) {
  int pos = 0;
  if (Mystrchr("oxX", configs->specifier)) {
    if (configs->specifier == 'x' || configs->specifier == 'X') {
      move_str(str);
    }
    if (configs->specifier == 'o') {
      str[pos++] = '0';
    } else {
      move_str(str);
    }
    str[pos++] = '0';
    if (configs->specifier != 'o') {
      if (configs->specifier == 'x') {
        str[pos] = 'x';
      } else {
        str[pos] = 'X';
      }
    }
  }
  if (Mystrchr("eEf", configs->specifier)) {
    if (!Mystrchr(str, '.')) {
      str[Mystrlen(str)] = '.';
    }
  }
}

void make_str_width(flags *configs, char *str) {
  int pos_str = (int)Mystrlen(str);
  if (configs->width > pos_str) {
    str[configs->width + 1] = '\0';
    while (pos_str >= 0) {
      str[configs->width--] = str[pos_str--];
    }
    for (pos_str = 0; pos_str <= configs->width; pos_str++) {
      if (Mystrchr("diopuxX", configs->specifier)) {
        if (configs->flag_zero && !configs->point) {
          str[pos_str] = 0;
        } else {
          str[pos_str] = ' ';
        }
      }
      if (Mystrchr("feEgGcs", configs->specifier)) {
        if (configs->flag_zero) {
          str[pos_str] = 0;

        } else {
          str[pos_str] = ' ';
        }
      }
    }
  }
}
void make_str_prec(flags *configs, char *str) {
  char *str_prec = MyNULL;
  str_prec = calloc(1024, sizeof(char));
  int pos = 0;
  if (str_prec != MyNULL) {
    if (Mystrchr("diouxX", configs->specifier)) {
      while (pos < configs->precision - (int)Mystrlen(str)) {
        str_prec[pos++] = '0';
      }
      for (int i = 0; str[i] != '\0'; i++) {
        str_prec[pos++] = str[i];
      }
      Mystrcpy(str, str_prec);
    }
    free(str_prec);
  }
}

void move_str(char *str) {
  int pos = (int)Mystrlen(str);
  str[pos + 1] = '\0';
  while (pos > 0) {
    str[pos] = str[pos - 1];
    pos--;
  }
}

void format_string(char **str, const char *value) {
  if (*str) {
    while (*value) {
      **str = *value;
      (*str)++;
      value++;
    }
  } else {
    while (*value) {
      (*str)++;
      value++;
    }
  }
}

void format_percentage(char *str, flags *configs) {
  Mystrcat(str, "%");
  make_str_prec(configs, str);
  make_str_flags(configs, str);
  make_str_width(configs, str);
}

//////////////////////////////////////
