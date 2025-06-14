#include "s21_string.h"
#define S21_NULL NULL

void *s21_trim(const char *src, const char *trim_chars) {
  char *result = S21_NULL;
  if (src != S21_NULL) {
    if (trim_chars == S21_NULL || trim_chars[0] == '\0') {
      trim_chars = " ";
    }
    s21_size_t len = s21_strlen(src);
    if (len) {
      int start = -1, end = -1, flag_first = 1, flag_last = 1, flag_break = 1;
      for (s21_size_t i = 0, j = len - 1; i < len && flag_break; i++, j--) {
        if (s21_strchr(trim_chars, src[i]) == S21_NULL && flag_first) {
          start = i;
          flag_first = 0;
        }
        if (s21_strchr(trim_chars, src[j]) == S21_NULL && flag_last) {
          end = j;
          flag_last = 0;
        }
        if (!flag_first && !flag_last) {
          flag_break = 0;
        }
      }
      result = calloc(end - start + 2, sizeof(char));
      if (result != S21_NULL) {
        for (int i = start, j = 0; i <= end; i++, j++) {
          result[j] = src[i];
        }
      }
    } else {
      result = calloc(2, sizeof(char));
    }
  }
  return result;
}

void *s21_to_upper(const char *str) {
  char *temp = (char *)str;
  char *string = S21_NULL;
  if (temp) {
    string = calloc(s21_strlen(str) + 1, sizeof(char));
    if (string) {
      for (int i = 0; temp[i] != '\0'; i++) {
        if (temp[i] >= 97 && temp[i] <= 122)
          string[i] = temp[i] - 32;
        else
          string[i] = temp[i];
      }
    }
  }
  return (void *)string;
}

void *s21_to_lower(const char *str) {
  char *temp = (char *)str;
  char *string = S21_NULL;
  if (temp) {
    string = calloc(s21_strlen(str) + 1, sizeof(char));
    if (string) {
      for (int i = 0; temp[i] != '\0'; i++) {
        if (str[i] >= 65 && str[i] <= 90)
          string[i] = temp[i] + 32;
        else
          string[i] = temp[i];
      }
    }
  }
  return (void *)string;
}

char *s21_strtok(char *str, const char *delim) {
  int flag = 0;
  static char *last;  // класс static позволяет сохранять значение переменной
  // между вызовами функции
  char *res;
  if (str == S21_NULL) {
    str = last;  // если str == S21_NULL, то берем последнее значение str
  }
  if (str == S21_NULL) {
    flag = 1;  // если str == S21_NULL, то возвращаем S21_NULL
  }
  if (!flag) {
    while (s21_is_delim(*str, delim)) {
      str++;  // пропускаем все разделители
    }
    if (*str == '\0') {
      flag = 1;  // если строка закончилась, то возвращаем S21_NULL
    }
    res = str;
    while (*str != '\0' && !s21_is_delim(*str, delim)) {
      str++;  // ищем конец строки или разделитель
    }
    if (*str != '\0') {
      *str = '\0';  // если строка не закончилась, то ставим терминатор
      str++;  // и переходим к следующему символу
    }
    last = str;  // запоминаем последнее значение str
  }
  if (flag) res = S21_NULL;
  return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  int needle_len = strlen(needle);
  if (needle_len == 0) {
    return (char *)haystack;
  }
  while (*haystack) {
    if (s21_strncmp(haystack, needle, s21_strlen(needle)) == 0) {
      return (char *)haystack;
    }
    haystack++;
  }
  return S21_NULL;
}

s21_size_t s21_strspn(const char *s1, const char *s2) {
  s21_size_t i, j;
  for (i = 0; s1[i] != '\0'; i++) {
    for (j = 0; s2[j] != '\0'; j++) {
      if (s1[i] == s2[j]) {
        break;
      }
    }
    if (s2[j] == '\0') {
      return i;
    }
  }
  return i;
}

char *s21_strrchr(const char *str, int ch) {
  const char *last = S21_NULL;
  while (*str != '\0') {
    if (*str == ch) {
      last = str;
    }
    str++;
  }
  if (*str == ch) {
    return (char *)str;
  }
  return (char *)last;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int i = 0;
  int j;
  for (; str1[i] != '\0'; i++) {
    for (j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        result = (char *)&str1[i];
        break;
      }
    }
    if (result != S21_NULL) {
      break;
    }
  }
  return result;
}

const char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[i] = src[i];
  }
  if (i < n) {
    dest[i] = '\0';
  }
  return dest;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      return str1[i] - str2[i];
    }
    if (str1[i] == '\0') {
      return 0;
    }
  }
  return 0;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_len = s21_strlen(dest);
  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    dest[dest_len + i] = src[i];
  }
  dest[dest_len + i] = '\0';
  return dest;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  while (*str != '\0') {
    ++len;
    ++str;
  }
  return len;
}

char *s21_strerror(int errnum) {
  char *msg = NULL;
#ifdef __APPLE__
  msg = strerror(errnum);
#else
  char errbuf[256];
#ifdef _POSIX_C_SOURCE
  strerror_r(errnum, errbuf, sizeof(errbuf));
#else
  if (strerror_r(errnum, errbuf, sizeof(errbuf)) != 0) {
    snprintf(errbuf, sizeof(errbuf), "Unknown error: %d", errnum);
  }
#endif
  msg = malloc(strlen(errbuf) + 1);
  if (msg != NULL) {
    s21_strcpy(msg, errbuf);
  }
#endif
  return msg;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;
  while (*str1 != '\0') {
    if (strchr(str2, *str1) != S21_NULL) {
      return count;
    }
    count++;
    str1++;
  }
  return count;
}

char *s21_strcpy(char *dest, const char *src) {
  char *temp = dest;
  while ((*temp++ = *src++) != '\0')
    ;
  return dest;
  //  free(dest);
}

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  if (str1 && str2) {
    int i = 0;
    while (str1[i] && str1[i] == str2[i]) {
      ++i;
    }
    result = str1[i] - str2[i];
  }
  return result;
}

char *s21_strchr(const char *str, int c) {
  while (*str != '\0') {  // проходим строку ищем симолы
    if (*str == c) {  // если ссимвол совпал с искомым
      return (char *)str;  // возвращаем указатель на этот символ
    }
    str++;  // продвигаемся по всем символам
  }
  if (c == '\0') {       // если находим 0
    return (char *)str;  // вовращаем указатель на строку
  } else {
    return S21_NULL;  // иначе искомый символ не найден
  }
}

char *s21_strcat(char *dest, const char *src) {
  char *temp = dest;
  while (*temp != '\0') {
    temp++;
  }
  while ((*temp++ = *src++) != '\0')
    ;
  return dest;
}

void *s21_memset(void *s, int c, s21_size_t n) {
  unsigned char *p = s;
  while (n--) {
    *p++ = (unsigned char)c;
  }
  return s;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *to = (char *)dest;
  char *from = (char *)src;

  char *tmp = (char *)malloc(sizeof(char) * n);

  if (tmp) {
    s21_memcpy(tmp, from, n);
    s21_memcpy(to, tmp, n);
    free(tmp);
  }

  return dest;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  char *temp_dest = dest;
  const char *temp_src = src;
  for (s21_size_t i = 0; i < s21_strlen(temp_src) + 1 && i < n; i++)
    temp_dest[i] = temp_src[i];
  return temp_dest;
}

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  unsigned const char *str1 = s1, *str2 = s2;
  int result = 0;
  while (n--) {
    if (*str1 != *str2) {
      return *str1 - *str2;
    }
    str1++;
    str2++;
  }
  return result;
}

void *s21_memchr(const void *ptr, int value, s21_size_t n) {
  const unsigned char *p = ptr;
  unsigned char val = value;

  for (s21_size_t i = 0; i < n; ++i) {
    if (p[i] == val) {
      return (void *)(p + i);
    }
  }

  return S21_NULL;
}

char *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t length_src =
      (src) ? s21_strlen(src) : 0;  //Надо будет использовать написанную функцию
  s21_size_t length_str =
      (str) ? s21_strlen(str) : 0;  //Надо будет использовать написанную функцию
  char *temp1 = (char *)src;
  char *temp2 = (char *)str;
  char *string = S21_NULL;
  if (temp1 && temp2 && start_index <= s21_strlen(src)) {
    string = calloc(length_src + length_str + 1, sizeof(char));
    if (string) {
      for (s21_size_t i = 0; i < start_index; i++) string[i] = temp1[i];
      for (s21_size_t i = start_index; i < start_index + length_str; i++)
        string[i] = temp2[i - start_index];
      for (s21_size_t i = start_index + length_str; i < length_src + length_str;
           i++)
        string[i] = temp1[i - length_str];
    }
  }
  return (void *)string;
}

int s21_is_delim(char c, const char *delim) {
  int res = 0;  // 1 если символ является разделителем, 0 если нет
  while (*delim != '\0') {
    if (c == *delim) {
      res = 1;
    }
    delim++;
  }
  return res;
}

#include "s21_string.h"
int s21_sprintf(char *str, const char *format, ...) {
  const char *target_saved =
      str;  // store the original address of the target string to calculate the
  // number of characters written later
  va_list args;
  va_start(args, format);

  int is_format = 0;  // flag to indicate whether the current character is a
  // format specifier or not
  while (*format) {
    if (s21_frmt_is_tokn(format) ==
        1) {  // check if the current character is a format specifier
      is_format = 1;
      format++;
    }
    if (is_format == 0) {  // if not a format specifier, just copy the character
      // to the target string
      *str = *format;
      str++;
      format++;
    }
    if (is_format == 1) {  // if it is a format specifier
      // const char *format = format;
      char specif =
          s21_tokn_get_specif(format);  // get the specific format character
      // (e.g. 'd', 's', 'x', etc.)
      int printed = 0;  // stores the number of characters written to the target
      // string for the current format specifier
      if (specif == SPECIFS[0] || specif == SPECIFS[15]) {  // %c, %%
        printed = s21_trgt_print_tokn_char(str, format, &args);
      }
      if (specif == SPECIFS[1] ||
          specif == SPECIFS[2] ||  // %d, %i, %u, %o, %x, %X
          specif == SPECIFS[8] || specif == SPECIFS[10] ||
          specif == SPECIFS[11] || specif == SPECIFS[12]) {
        printed = s21_trgt_print_tokn_num(str, format, &args);
      }
      if (specif == SPECIFS[3] ||
          specif == SPECIFS[4] ||  // %f, %F, %e, %E, %g, %G
          specif == SPECIFS[5] || specif == SPECIFS[6] ||
          specif == SPECIFS[7]) {
        printed = s21_trgt_print_tokn_ratio(str, format, &args);
      }
      if (specif == SPECIFS[9]) {  // %s
        printed = s21_trgt_print_tokn_str(str, format, &args);
      }
      if (specif == SPECIFS[13]) {  // %p
        printed = s21_trgt_print_tokn_ptr(str, format, &args);
      }
      if (specif == SPECIFS[14]) {  // %n
        printed = 0;
        int *to_write_here = va_arg(args, int *);
        *to_write_here = str - target_saved;
      }
      str += printed;

      /* move format pointer to the next token */
      format += s21_tokn_get_str_len(format);
      is_format = 0;
    }
    *str = '\0';
  }

  /* clean up the argument list */
  va_end(args);
  return str - target_saved;
}

char *s21_tokn_skip_part(const char *format, unsigned int i) {
  // If i is greater than 0.
  if (i--) /* flags */
    // Loop through the string "format".
    while (*format && s21_strchr(FLAGS, *format))
      // Move to the next character.
      format++;

  // If i is greater than 0.
  if (i--) { /* width */
    // Check if the current character is the additional integer sign.
    if (*format == ADDIT_INT_SIGN)
      // If it is, move to the next character.
      format++;
    else
      // Loop through the string "format" as long as the current character is
      // a digit.
      while (*format && s21_strchr(DIGITS, *format))
        // Move to the next character.
        format++;
  }

  // If i is greater than 0.
  if (i--) { /* precision */
    // Check if the current character is the precision sign.
    if (*format == PRECIS_SIGN) {
      // If it is, move to the next character.
      format++;

      // Check if the next character is the additional integer sign.
      if (*format == ADDIT_INT_SIGN)
        // If it is, move to the next character.
        format++;
      else
        // Loop through the string "format" as long as the current character
        // is a digit.
        while (*format && s21_strchr(DIGITS, *format))
          // Move to the next character.
          format++;
    }
  }

  // If i is greater than 0.
  if (i--) /* length-specifier */
    // Check if the current character is one of the length-specifiers.
    if (*format && s21_strchr(TOKN_LENS, *format))
      // If it is, move to the next character.
      format++;

  // If i is greater than 0.
  if (i) /* specifier */
    // Check if the current character is one of the specifiers.
    if (*format && s21_strchr(SPECIFS, *format))
      // If it is, move to the next character.
      format++;

  // Return the final value of "format".
  return (char *)format;
}

int s21_tokn_have_flag(const char *format, char flag) {
  // Loop through the string "format".
  while (s21_strchr(FLAGS, *format)) {
    // Check if the current character is equal to the "flag" argument.
    if (*format == flag) return 1;
    // Move to the next character.
    format++;
  }
  // If the "flag" argument is not found, return 0.
  return 0;
}

int s21_tokn_get_width(const char *format) {
  // Skip the first character in the string "format".
  format = s21_tokn_skip_part(format, 1);

  // Initialize the result to -1.
  int result = -1;

  // Check if the current character is the additional integer sign.
  if (*format == ADDIT_INT_SIGN) {
    // If it is, set the result to -2.
    result = -2;
  }

  // Attempt to parse a long integer from the string "format".
  if (s21_atol(format)) {
    // If a long integer is found, set the result to the integer value.
    result = s21_atol(format);
  }

  // Return the final value of result.
  return result;
}

int s21_tokn_get_precision(const char *format) {
  // Skips the first 2 characters in the string "format".
  format = s21_tokn_skip_part(format, 2);

  // Initialize the result to -1.
  int result = -1;

  // Check if the current character is the precision sign.
  if (*format == PRECIS_SIGN) {
    // If it is, move to the next character.
    format++;

    // Initialize result to -3.
    result = -3;

    // Check if the next character is the additional integer sign.
    if (*format == ADDIT_INT_SIGN) {
      // If it is, set the result to -2.
      result = -2;
    }

    // Attempt to parse a long integer from the string "format".
    if (s21_atol(format)) {
      // If a long integer is found, set the result to the integer value.
      result = s21_atol(format);
    } else if (*format == '0') {
      /*  .. == '0' --- because s21_atol() returns 0 as fail, we should
       *      check for 0 value additionally
       */
      // If the first character after the precision sign is 0, set the result
      // to 0.
      result = 0;
    }
  }

  // Return the final value of result.
  return result;
}

/*
s21_tokn_get_len: Returns the length (h, l, or L) of the format string if it
exists, otherwise '\0' is returned.

format: The format string to be parsed.

Returns:
  The length of the format string or '\0' if no length is specified.
*/
char s21_tokn_get_len(const char *format) {
  // Skips the first 3 parts of the format string (flags, width, and
  // precision)
  format = s21_tokn_skip_part(format, 3);

  // If the next character in the format string is a length (h, l, or L)
  if (s21_strchr(TOKN_LENS, *format)) {
    // Return the length character
    return *format;
  }
  // Return '\0' if no length is specified
  return '\0';
}

/*
s21_tokn_get_specif: Returns the specifier of the format string if it exists,
otherwise '\0' is returned.

format: The format string to be parsed.

Returns:
  The specifier of the format string or '\0' if no specifier is specified.
*/
char s21_tokn_get_specif(const char *format) {
  const char *specifier = s21_tokn_skip_part(format, 4);
  return (*specifier && s21_strchr(SPECIFS, *specifier)) ? *specifier : '\0';
}
/*
s21_tokn_get_str_len: Returns the length of the format string from the current
position to the end of the string.

format: The format string to be parsed.

Returns:
  The length of the format string from the current position to the end of the
string.
*/
int s21_tokn_get_str_len(const char *format) {
  // Returns the length of the format string from the current position (after
  // the first 5 parts) to the end of the string.
  return s21_tokn_skip_part(format, 5) - format;
}

/* Returns 1 if the input string format starts with a token sign, else 0 */
int s21_frmt_is_tokn(const char *format) {
  int result = 0;
  if (*format == TOKN_SIGN) {
    format++;  // move to next char after the token sign
    if (s21_tokn_get_specif(
            format)) {  // check if the rest of the string is a valid token
      result = 1;
    }
  }
  return result;
}

/* Writes the string representation of unsigned long n to str and returns the
 * length of the written string */
int s21_trgt_print_ulong(char *str, unsigned long n) {
  const char *target_saved = str;

  int n_len = s21_udecim_get_str_len(n);  // get the number of digits in n
  while (n_len > 0) {
    unsigned long divisor = s21_ulong_get_pow(
        10, n_len - 1);  // get the divisor for the current digit
    unsigned long curr_d = n / divisor;  // get the current digit
    char curr_c =
        '0' + curr_d;  // convert the digit to its character representation
    *str = curr_c;     // write the digit to str
    str++;
    n %= divisor;  // reduce n by the digit we just wrote
    n_len--;
  }

  return str - target_saved;  // return the length of the written string
}

// This function prints a long double number to a string
int s21_trgt_print_uldouble(char *str, long double ld, int precis_len) {
  // Save the starting position of the target string
  const char *target_saved = str;

  // Check if the number is not a number (NaN)
  if (isnan(ld)) {
    // Copy "nan" to the target string and return 3 (length of "nan")
    s21_memcpy(str, "nan", 3);
    return 3;
  }
  // Check if the number is positive or negative infinity
  if (ld == INFINITY) {
    // Copy "inf" to the target string and return 3 (length of "inf")
    s21_memcpy(str, "inf", 3);
    return 3;
  }

  // Get the integer part of the number
  unsigned long decim_part = (long)ld;
  // Print the integer part of the number
  str += s21_trgt_print_ulong(str, decim_part);
  // Subtract the integer part from the number to get the fractional part
  ld -= decim_part;

  // Check if the '#' flag was passed to the function
  if (precis_len == -1) {
    // Add a '.' character to the target string
    *str = '.';
    str++;
  }

  // Check if a precision value was passed to the function
  if (precis_len > 0) {
    // Add a '.' character to the target string
    *str = '.';
    str++;
    // Get the fractional part of the number, rounded to the specified
    // precision
    long double after_part;
    after_part = ld * s21_ulong_get_pow(10, precis_len);
    after_part = round(after_part);
    // Get the length of the fractional part as a string
    int after_part_len = s21_udecim_get_str_len((unsigned long)after_part);
    // Calculate the number of zeros that need to be added to the fractional
    // part
    int zeros_count = precis_len - after_part_len;
    // Ensure that zeros_count is non-negative
    if (zeros_count < 0) {
      zeros_count = 0;
    }
    // Add zeros to the target string
    s21_memset(str, '0', zeros_count);
    str += zeros_count;
    // Print the fractional part of the number
    str += s21_trgt_print_ulong(str, (unsigned long)after_part);
  }

  // Return the length of the printed string
  return str - target_saved;
}

// This function prints a long double number in scientific notation
int s21_trgt_print_e_uldouble(char *str, long double ld, int precis_len,
                              char e_sign) {
  // Save the starting position of the target string
  const char *target_saved = str;

  // Initialize exponent e to zero
  int e = 0;

  // Add LDBL_EPSILON to the long double number
  ld += LDBL_EPSILON;

  // Keep dividing the number by 10 until it is >= 1
  while (ld < 1) {
    e--;
    ld *= 10;
  }

  // Keep multiplying the number by 10 until it is <= 10
  while (ld > 10) {
    e++;
    ld /= 10;
  }

  // Print the mantissa (first part of the scientific notation)
  str += s21_trgt_print_uldouble(str, ld, precis_len);

  // Add the e_sign character to the string
  *str = e_sign;
  str++;

  // Check if the exponent is negative
  if (e < 0) {
    // Add a '-' sign to indicate a negative exponent
    *str = '-';
    str++;
    e = -e;
  } else {
    // Add a '+' sign to indicate a positive exponent
    *str = '+';
    str++;
  }

  // Convert the exponent to two characters and add them to the string
  *str = '0' + e / 10;
  str++;
  *str = '0' + e % 10;
  str++;

  // Return the length of the printed string
  return str - target_saved;
}

int s21_trgt_print_base_ulong(char *str, unsigned long n, const char *base) {
  // Save the original position of the target string for later use
  const char *target_saved = str;
  int base_n = s21_strlen(base);

  // Recursively convert the value to the target base
  if (n / base_n) {
    str += s21_trgt_print_base_ulong(str, n / base_n, base);
  }

  // Add the least significant digit to the target string
  *str = base[n % base_n];
  str++;

  return str - target_saved;
}

int s21_trgt_print_tokn_char(char *str, const char *format, va_list *args) {
  const char *target_saved = str;

  int is_prequel = s21_tokn_have_flag(format, FLAGS[0]);

  int width = s21_tokn_get_width(format);
  if (width == -2) {
    width = va_arg(*args, int);
  }
  if (width < 0) {
    is_prequel = 1;
    width = -width;
  }

  int fill_len = width - 1;
  if (fill_len < 0) {
    fill_len = 0;
  }

  int precis_len = s21_tokn_get_precision(format);
  if (precis_len == -1) {
    precis_len = 6;
  }
  if (precis_len == -2) {
    precis_len = va_arg(*args, int);
  }
  if (precis_len < 0) {
    precis_len = 0;
  }

  char tokn_specif = s21_tokn_get_specif(format);

  char tokn_c = '\0';
  if (tokn_specif == SPECIFS[0]) {
    tokn_c = (char)va_arg(*args, int);
  }
  if (tokn_specif == SPECIFS[15]) {
    tokn_c = TOKN_SIGN;
  }

  char fill_symb = ' ';
  if (s21_tokn_have_flag(format, FLAGS[4]) && is_prequel == 0) {
    fill_symb = '0';
  }

#ifdef __APPLE__
  if (is_prequel == 0) {
    s21_memset(str, fill_symb, fill_len);
    str += fill_len;
  }
  *str = tokn_c;
  str++;
  if (is_prequel) {
    s21_memset(str, fill_symb, fill_len);
    str += fill_len;
  }
#else  // For GNU/Linux (that uses glibc)
  if (tokn_specif == SPECIFS[0]) {
    if (is_prequel == 0) {
      s21_memset(str, fill_symb, fill_len);
      str += fill_len;
    }
    *str = tokn_c;
    str++;
    if (is_prequel) {
      s21_memset(str, fill_symb, fill_len);
      str += fill_len;
    }
  }
  if (tokn_specif == SPECIFS[15]) {
    *str = tokn_c;
    str++;
  }
#endif

  return str - target_saved;
}

int s21_trgt_print_tokn_num(char *str, const char *format, va_list *args) {
  const char *target_saved = str;

  int is_prequel = s21_tokn_have_flag(format, FLAGS[0]);

  int width = s21_tokn_get_width(format);
  if (width == -2) {
    width = va_arg(*args, int);
  }
  if (width == -1) {
    width = 0;
  }
  if (width < 0) {
    is_prequel = 1;
    width = -width;
  }

  int precis = s21_tokn_get_precision(format);
  int is_precis_provided = 1;
  if (precis == -3) {
    /* -3 --- it means that PRECIS_SIGN was provided */
    precis = 0;
  }
  if (precis == -1) {
    /* -1 --- it means that PRECIS_SIGN was not provided */
    precis = 0;
    is_precis_provided = 0;
  }
  if (precis == -2) {
    precis = va_arg(*args, int);
  }
  /*  precis --- works here as minimum digits counter to output */

  long tokn_num = va_arg(*args, long);

  if (s21_tokn_get_specif(format) == SPECIFS[1] ||
      s21_tokn_get_specif(format) == SPECIFS[2]) {
    tokn_num = (int)tokn_num;
  }
  if (s21_tokn_get_len(format) == TOKN_LENS[0]) {
    tokn_num = (short)tokn_num;
  }

  char sign = '\0';
  if (s21_tokn_have_flag(format, FLAGS[1])) {
    sign = '+';
  }
  if (tokn_num < 0 && s21_tokn_get_specif(format) != SPECIFS[10]) {
    sign = '-';
  }
  if (sign == '\0' && s21_tokn_have_flag(format, FLAGS[2])) {
    sign = ' ';
  }

  char *base = DIGITS;
  char *prefix_0x = s21_NULL;
  if (s21_tokn_get_specif(format) == SPECIFS[8]) {
    base = BASE8;
    prefix_0x = "0";
  }
  if (s21_tokn_get_specif(format) == SPECIFS[11]) {
    base = BASE16LOW;
    prefix_0x = "0x";
  }
  if (s21_tokn_get_specif(format) == SPECIFS[12]) {
    base = BASE16UP;
    prefix_0x = "0X";
  }
  if (s21_tokn_have_flag(format, FLAGS[3]) == 0 || tokn_num == 0) {
    prefix_0x = s21_NULL;
  }

  unsigned long tokn_unum;
  if (s21_tokn_get_specif(format) == SPECIFS[1] ||
      s21_tokn_get_specif(format) == SPECIFS[2]) {
    tokn_unum = tokn_num >= 0 ? tokn_num : -tokn_num;
  } else {
    tokn_unum = tokn_num;
  }

  int tokn_unum_len = s21_base_unum_get_str_len(tokn_unum, base);
  if (is_precis_provided && precis == 0 && tokn_unum == 0) {
    tokn_unum_len = 0;
  }

  int precis_prefix_len = precis - tokn_unum_len;
  if (precis_prefix_len < 0) {
    precis_prefix_len = 0;
  }

  int fill_len = 0;
  if (width) {
    fill_len = width - precis_prefix_len - tokn_unum_len;
  }
  if (sign) {
    fill_len--;
  }
  if (prefix_0x) {
    fill_len -= s21_strlen(prefix_0x);
  }
  if (fill_len < 0) {
    fill_len = 0;
  }

  char fill_symb = ' ';
  if (s21_tokn_have_flag(format, FLAGS[4]) && is_prequel == 0) {
    fill_symb = '0';
  }
  if (precis_prefix_len || precis > 0) {
    fill_symb = ' ';
  }

  if (is_prequel == 0) {
    if (fill_symb == '0' && sign) {
      *str = sign;
      str++;
    }
    if (fill_symb == ' ' || prefix_0x == s21_NULL) {
      s21_memset(str, fill_symb, fill_len);
      str += fill_len;
    }
  }
  if (fill_symb == ' ' && sign) {
    *str = sign;
    str++;
  }
  if (prefix_0x) {
    s21_strcpy(str, prefix_0x);
    str += s21_strlen(prefix_0x);
    if (fill_symb == '0') {
      s21_memset(str, fill_symb, fill_len);
      str += fill_len;
    }
  }
  if (precis_prefix_len) {
    s21_memset(str, '0', precis_prefix_len);
    str += precis_prefix_len;
  }
  if ((is_precis_provided && precis == 0 && tokn_unum == 0) == 0) {
    /*  precis == 0 && tokn_unum == 0 --- because we should not print
     *      value 0 if provided precis is 0
     */
    int printed = s21_trgt_print_base_ulong(str, tokn_unum, base);
    str += printed;
  }
  if (is_prequel) {
    s21_memset(str, fill_symb, fill_len);
    str += fill_len;
  }

  return str - target_saved;
}

int s21_trgt_print_tokn_str(char *str, const char *format, va_list *args) {
  // Save the original pointer to str
  const char *target_saved = str;

  // Check if the FLAGS[0] is set in the format string
  int is_prequel = s21_tokn_have_flag(format, FLAGS[0]);

  // Get the width of the token from the format string or from the arguments
  int tokn_width = s21_tokn_get_width(format);
  if (tokn_width == -2) {
    tokn_width = va_arg(*args, int);
  }
  // If the width is set to -1, set it to 0
  if (tokn_width == -1) {
    tokn_width = 0;
  }
  // If the width is negative, set the is_prequel flag to 1 and make the width
  // positive
  if (tokn_width < 0) {
    is_prequel = 1;
    tokn_width = -tokn_width;
  }

  // Get the precision of the token from the format string or from the
  // arguments
  int tokn_precis = s21_tokn_get_precision(format);
  if (tokn_precis == -2) {
    tokn_precis = va_arg(*args, int);
  }
  // tokn_precis is used as the length of the string
  /*  tokn_precis --- works here as str len   */

  // Get the string from the arguments
  char *tokn_str = va_arg(*args, char *);
  // If the precision is set to -1 or greater than the length of the string,
  // set it to the length of the string
  if (tokn_precis == -1 || tokn_precis > (int)s21_strlen(tokn_str)) {
    tokn_precis = s21_strlen(tokn_str);
  }
  // If the precision is negative, set it to 0
  if (tokn_precis < 0) {
    tokn_precis = 0;
  }

  // Calculate the fill length as the difference between the width and
  // precision
  int fill_len = tokn_width - tokn_precis;
  // If the fill length is negative, set it to 0
  if (fill_len < 0) {
    fill_len = 0;
  }

  // If is_prequel is 0, fill the string with spaces before the token string
  if (is_prequel == 0) {
    s21_memset(str, ' ', fill_len);
    str += fill_len;
  }

  // Copy the token string to the target string with the given precision
  s21_strncpy(str, tokn_str, tokn_precis);
  str += tokn_precis;

  if (is_prequel) {
    s21_memset(str, ' ', fill_len);
    str += fill_len;
  }

  return str - target_saved;
}

int s21_trgt_print_tokn_ratio(char *str, const char *format, va_list *args) {
  // Store the initial value of the target string pointer
  const char *target_saved = str;

  // Get the format specifier from the format string
  char tokn_specif = s21_tokn_get_specif(format);

  // Check if the ' ' flag is present in the format string
  int is_prequel = s21_tokn_have_flag(format, FLAGS[0]);

  // Get the width value from the format string or the argument list
  int width = s21_tokn_get_width(format);
  if (width == -2) {
    width = va_arg(*args, int);
  }
  // Make sure the width value is positive
  if (width < 0) {
    is_prequel = 1;
    width = -width;
  }

  // Get the precision value from the format string or the argument list
  int precis_len = s21_tokn_get_precision(format);
  if (precis_len == -1) {
    precis_len = 6;
  }
  if (precis_len == -2) {
    precis_len = va_arg(*args, int);
  }
  if (precis_len <= -3) {
    precis_len = 6;
  }
  // Set the precision value to 1 for %f and %F if it's 0
  if (precis_len == 0 &&
      (tokn_specif == SPECIFS[6] || tokn_specif == SPECIFS[7])) {
    precis_len = 1;
  }

  // Get the token ratio value from the argument list
  long double tokn_ratio;
  if (s21_tokn_get_len(format) == TOKN_LENS[2]) {
    tokn_ratio = va_arg(*args, long double);
  } else {
    tokn_ratio = va_arg(*args, double);
  }

  // Determine the sign of the token ratio value
  char sign = '\0';
  if (tokn_ratio >= 0 && s21_tokn_have_flag(format, FLAGS[1])) {
    sign = '+';
  }
  if (tokn_ratio < 0) {
    sign = '-';
    tokn_ratio = -tokn_ratio;
  }

  // Determine if the "e" representation of the token ratio is shorter
  int is_e_shorter = 0;
  int non_precis_part_len = s21_udecim_get_str_len((unsigned long)tokn_ratio);
  if (tokn_specif == SPECIFS[3] || tokn_specif == SPECIFS[4]) {
    non_precis_part_len = 5;

  } else if (tokn_specif == SPECIFS[6] || tokn_specif == SPECIFS[7]) {
    if (s21_tokn_have_flag(format, FLAGS[3])) {
      int e = s21_e_uratio_get_e(tokn_ratio);
      e++;
      //   e++ --- because in "0.052", e will have value of -2, but we
      //       need to substract only 1 from precis_len
      precis_len = precis_len - e;
      if (precis_len < 0) {
        precis_len = 0;
      }
    } else {
      int actual_precis_len =
          s21_uratio_precis_get_str_len(tokn_ratio, precis_len);
      int actual_e_precis_len =
          s21_e_uratio_precis_get_str_len(tokn_ratio, precis_len);

      char buff[500];

      int len1 = s21_trgt_print_uldouble(buff, tokn_ratio, actual_precis_len);
      int len2 =
          s21_trgt_print_e_uldouble(buff, tokn_ratio, actual_e_precis_len, 'e');
      if (len2 < len1) {
        is_e_shorter = 1;
        precis_len = actual_e_precis_len;
        non_precis_part_len = 5;
      } else {
        int e = s21_e_uratio_get_e(tokn_ratio);
        precis_len = precis_len - e - 1;
        precis_len = s21_uratio_precis_get_str_len(tokn_ratio, precis_len);
      }
    }
  }

  int is_point_forced = s21_tokn_have_flag(format, FLAGS[3]);

  int is_pre_whitespace = 0;
  if (sign == '\0' && s21_tokn_have_flag(format, FLAGS[2])) {
    is_pre_whitespace = 1;
  }

  int fill_len = width - precis_len - non_precis_part_len;
  if (is_pre_whitespace) {
    fill_len--;
  }
  if (precis_len || is_point_forced) {
    /* For a common */
    fill_len--;
  }
  if (sign) {
    fill_len--;
  }
  if (fill_len < 0) {
    fill_len = 0;
  }

  char fill_symb = ' ';
  if (s21_tokn_have_flag(format, FLAGS[4]) && is_prequel == 0) {
    fill_symb = '0';
  }

  char e_sign = '\0';
  if (tokn_specif == SPECIFS[3] || tokn_specif == SPECIFS[6]) {
    e_sign = 'e';
  }
  if (tokn_specif == SPECIFS[4] || tokn_specif == SPECIFS[7]) {
    e_sign = 'E';
  }

  if (precis_len == 0 && is_point_forced) {
    precis_len = -1;
    /*  -1 --- indicates flag '#'   */
  }

  if (is_pre_whitespace) {
    *str = ' ';
    str++;
  }
  if (is_prequel == 0) {
    if (fill_symb == '0' && sign) {
      *str = sign;
      str++;
    }
    s21_memset(str, fill_symb, fill_len);
    str += fill_len;
  }
  if (fill_symb == ' ' && sign) {
    *str = sign;
    str++;
  }
  if (tokn_specif == SPECIFS[5]) {
    str += s21_trgt_print_uldouble(str, tokn_ratio, precis_len);
  } else if (tokn_specif == SPECIFS[3] || tokn_specif == SPECIFS[4]) {
    str += s21_trgt_print_e_uldouble(str, tokn_ratio, precis_len, e_sign);

  } else if (tokn_specif == SPECIFS[6] || tokn_specif == SPECIFS[7]) {
    if (is_e_shorter) {
      str += s21_trgt_print_e_uldouble(str, tokn_ratio, precis_len, e_sign);
    } else {
      str += s21_trgt_print_uldouble(str, tokn_ratio, precis_len);
    }
  }
  if (is_prequel) {
    s21_memset(str, fill_symb, fill_len);
    str += fill_len;
  }

  return str - target_saved;
}

int s21_trgt_print_tokn_ptr(char *str, const char *format, va_list *args) {
  const char *target_saved = str;

  int is_prequel = s21_tokn_have_flag(format, FLAGS[0]);

  int width = s21_tokn_get_width(format);
  if (width == -2) {
    width = va_arg(*args, int);
  }
  if (width == -1) {
    width = 0;
  }
  if (width < 0) {
    is_prequel = 1;
    width = -width;
  }

  int precis = s21_tokn_get_precision(format);
  if (precis == -3) {
    precis = 0;
  }
  if (precis == -2) {
    precis = va_arg(*args, int);
  }
  if (precis == -1) {
    precis = 0;
  }
  if (precis < 0) {
    precis = 0;
  }

  s21_size_t p = va_arg(*args, s21_size_t);
  /*  s21_size_t --- it's the same as pointer */

  int is_null = 0;
  if (p == 0) {
    is_null = 1;
#ifdef __APPLE__
    precis = 1;
    /*  .. = 1 --- because apple's libc printf 0x0 in NULL case. 1 here is
     *      for end 0 */
#endif
  }

  int p_len = s21_base_unum_get_str_len(p, BASE16LOW);
  if (is_null) {
    p_len = 0;
  }

  int zero_prefix_len = PTR_LEN - p_len;
  if (zero_prefix_len < 0) {
    zero_prefix_len = 0;
  }
#if defined(__APPLE__) || defined(__MUSL__)
  zero_prefix_len = 0;
  /*  ... = 0 --- apple's libc and musl doesn't print prefix extra zeros on
   *      pointers like 0x00052ab3f1c9b. They print just 0x52ab3f1c9b. */
#endif

  int fill_len = width - 2 - zero_prefix_len - p_len;
  /*  ... - 2 --- because "0x" prefix has length of 2 */
  if (is_null) {
#ifndef __APPLE__  // If NOT __APPLE__
    fill_len = width - s21_strlen(PTR_NULL_STR);
#endif

    fill_len -= precis;
  }
  if (fill_len < 0) {
    fill_len = 0;
  }

  if (is_prequel == 0) {
    s21_memset(str, ' ', fill_len);
    str += fill_len;
  }
  if (is_null) {
    s21_strcpy(str, PTR_NULL_STR);
    str += s21_strlen(PTR_NULL_STR);
#ifdef __APPLE__
    *str++ = '0';
    *str++ = 'x';
    s21_memset(str, '0', precis);
    str += precis;
#endif
  } else {
    *str++ = '0';
    *str++ = 'x';
    s21_memset(str, '0', zero_prefix_len);
    str += zero_prefix_len;
    str += s21_trgt_print_base_ulong(str, p, BASE16LOW);
  }
  if (is_prequel) {
    s21_memset(str, ' ', fill_len);
    str += fill_len;
  }

  return str - target_saved;
}

int s21_base_unum_get_str_len(unsigned long n, char *base) {
  int result = 0;
  // divide n by the length of the base until n is less than the length of the
  // base
  while (n >= (unsigned long)s21_strlen(base)) {
    result++;
    n /= (unsigned long)s21_strlen(base);
  }
  result++;
  return result;
}

int s21_udecim_get_str_len(unsigned long n) {
  // delegate to s21_base_unum_get_str_len function for getting the length
  return s21_base_unum_get_str_len(n, DIGITS);
}

unsigned long s21_ulong_get_pow(unsigned long n, int pow) {
  unsigned long result = 0;
  // pow is 0, return 1
  if (pow == 0) {
    result = 1;
  }
  // pow is not 0, start with result = n
  if (pow) {
    result = n;
    pow--;
  }
  // multiply n with itself pow times
  while (pow) {
    result *= n;
    pow--;
  }
  return result;
}

long s21_atol(const char *str) {
  long result = 0;
  int is_minus = 0;
  // check if the number is negative
  if (*str == '-') {
    is_minus = 1;
    str++;
  }
  // loop through the string, convert each digit to a long integer and add to
  // the result
  while (*str && s21_strchr(DIGITS, *str)) {
    result *= 10;
    result += *str - '0';
    str++;
  }
  return is_minus ? -result : result;
}

int s21_uratio_precis_get_str_len(long double ld, int precis_len) {
  // Subtract the integer part of the long double value
  ld -= (long)ld;

  char buff[500];
  // Convert the fractional part to a string
  s21_trgt_print_uldouble(buff, ld, precis_len);

  int i = precis_len - 1;
  // Remove trailing zeros from the string
  while (buff[2 + i] == '0') {
    i--;
  }

  // Return the length of the string, plus 2 for "0."
  return i + 1;
}

int s21_e_uratio_precis_get_str_len(long double ld, int precis_len) {
  int e = 0;
  // Add a small positive number to the long double value
  ld += LDBL_EPSILON;
  // Scale the long double value to between 1 and 10
  while (ld < 1) {
    e--;
    ld *= 10;
  }
  while (ld > 10) {
    e++;
    ld /= 10;
  }
  // Get the string length of the fractional part
  return s21_uratio_precis_get_str_len(ld, precis_len);
}

int s21_e_uratio_get_e(long double ld) {
  int e = 0;
  // Scale the long double value to between 1 and 10
  while (ld < 1) {
    e--;
    ld *= 10;
  }
  while (ld > 10) {
    e++;
    ld /= 10;
  }
  // Return the value of the exponent
  return e;
}

// //////////////////////SsCANF/////////////////////////////////

int s21_sscanf(const char *src, const char *format, ...) {
  sscanf_format arguments = {0};
  va_list va;
  char *string = (char *)src;
  va_start(va, format);
  int rez = 0;
  char *start = string;
  int zero_flag = 1;
  arguments.float_stop_rez = 0;
  arguments.flag_for_i = 0;

  if (*string == '\0' && *format == '\0') {
    zero_flag = 0;
  } else {
    rez = sscanf_check(string);
  }

  while (*format && zero_flag) {
    if (is_space_enter_tab(*format)) {
      while (*(format + 1) != '\0' && is_space_enter_tab(*string)) {
        ++string;
      }

      format++;
      continue;
    }
    if (*format != '%') {
      if (*string == *format) {
        string++;
        format++;
        continue;
      } else {
        break;
      }
    } else {
      format++;
      if (*format == '%') {
        if (*string == '%') {
          string++;
          format++;
          continue;
        } else {
          break;
        }
      }
    }
    format = sscanf_flags(format, &arguments);
    format = sscanf_width(format, &arguments);
    format = sscanf_length(format, &arguments);
    arguments.specifier = *format;
    if (*string == '\0' && arguments.specifier != 'n') {
      break;
    }
    if ((arguments.asterisk) != -1) {
      arguments.adress = va_arg(va, void *);
    }
    if ((arguments.adress != 0 || (arguments.asterisk) == -1) &&
        !arguments.fail) {
      write_to_memory(&string, &arguments, &rez, start);
      sscanf_format_zero(&arguments);
    }
    format++;
  }
  va_end(va);
  return rez;
}

// Записываем строку (спецификатор "s"):

void write_string(char **buf, sscanf_format *arguments, int *rez) {
  char buffer[BUFF_SIZE] = {'\0'};
  int size = 0;
  while (**buf != '\0' && !is_space_enter_tab(**buf) && !arguments->fail) {
    buffer[size] = **buf;
    ++(*buf);
    ++size;
    if ((arguments->width && size >= arguments->width) ||
        is_space_enter_tab(**buf)) {
      break;
    }
  }
  buffer[size] = '\0';
  if ((arguments->asterisk) != -1) {
    s21_strcpy((char *)arguments->adress, buffer);
    ++(*rez);
  }
}

// Записываем char (спецификатор "c"):

void write_character(char **buf, sscanf_format *arguments, int *rez) {
  char symbol;
  symbol = **buf;
  if (arguments->width > 0) {
    for (int i = 0; i < arguments->width; i++) {
      ++(*buf);
    }
  } else {
    ++(*buf);
  }
  if ((arguments->asterisk) != -1) {
    *(char *)arguments->adress = symbol;
    ++(*rez);
  }
}

//  Записываем int (спецификатор "d"):

void write_integer(char **buf, sscanf_format *arguments, int *rez) {
  long long int result = 0;
  int stop_i = 0;

  if (s21_strspn(*buf, "0x") == 2) {
    stop_i = 1;
  }
  if (s21_strspn(*buf, "0123456789+-")) {
    if (!(s21_strspn(*buf, "+-") > 1)) {
      result = mod_atoi(buf, arguments);
      if (arguments->asterisk != -1) {
        if (arguments->length == TRUE) {
          *(short int *)arguments->adress = (short int)result;
        } else if (arguments->length == SHORT_LENGTH) {
          *(long int *)arguments->adress = (long int)result;
        } else if (arguments->length == LONG_LENGTH) {
          *(long long int *)arguments->adress = (long long int)result;
        } else {
          *(int *)arguments->adress = (int)result;
        }
      }

      if ((arguments->asterisk) != -1 && arguments->flag_for_i != 1 &&
          !arguments->fail) {
        *rez = *rez + 1;
        if (stop_i == 1) {
          arguments->flag_for_i = 1;
        }
      }
    }
  }
}

// Записываем int (8ричное/10ричное/16ричное) (спецификатор "i"):

void write_i_integer(char **buf, sscanf_format *arguments, int *rez) {
  long long int result = 0;
  int base = 0;
  if ((s21_strspn(*buf, "0x") == 2) || (s21_strspn(*buf, "0X") == 2)) {
    base = 16;
  } else if (s21_strspn(*buf, "0") == 1) {
    base = 8;
  } else if (s21_strspn(*buf, "0123456789+-")) {
    base = 10;
  }
  if (base) {
    result = write_8_16(buf, arguments, rez, base);
    if (arguments->asterisk != -1) {
      if (arguments->length == TRUE) {
        *(short int *)arguments->adress = (short int)result;
      } else if (arguments->length == SHORT_LENGTH) {
        *(long int *)arguments->adress = (long int)result;
      } else if (arguments->length == LONG_LENGTH) {
        *(long long int *)arguments->adress = (long long int)result;
      } else {
        *(int *)arguments->adress = (int)result;
      }
      if (arguments->flag_for_i != 1) {
        ++(*rez);
      }
    }
  }
}

//  Записываем float (спецификаторы "f", "e", "E", "g", "G"):

void write_float(char **buf, sscanf_format *arguments, int *rez) {
  float result_f = 0;
  double result_d = 0;
  long double result_ld = 0;

  if (s21_strspn(*buf, "infINF") == 3) {
    result_f = INFINITY;
    *(float *)arguments->adress = (float)result_f;
    (*buf) += 3;
    *rez += 1;
  } else if (s21_strspn(*buf, "NANnan") == 3) {
    result_f = NAN;
    *(float *)arguments->adress = (float)result_f;
    (*buf) += 3;
    *rez += 1;
  } else if (s21_strspn(*buf, "0123456789+-") ||
             s21_strspn(*buf, ".0123456789+-")) {
    if (arguments->length == SHORT_LENGTH) {
      result_d = sscanf_atof(buf, arguments);
      if ((arguments->asterisk) != -1 && arguments->float_stop_rez < 2) {
        *(double *)arguments->adress = (double)result_d;
      }
    } else if (arguments->length == DOUBLE_LENGTH) {
      result_ld = sscanf_atof(buf, arguments);
      if ((arguments->asterisk) != -1 && arguments->float_stop_rez < 2) {
        *(long double *)arguments->adress = (long double)result_ld;
      }
    } else {
      result_f = sscanf_atof(buf, arguments);
      if ((arguments->asterisk) != -1 && arguments->float_stop_rez < 2) {
        *(float *)arguments->adress = (float)result_f;
      }
    }

    if ((arguments->asterisk) != -1 && (arguments->float_stop_rez) != 2) {
      ++(*rez);
    }
  }
}

//  Разбор по спецификаторам:

void write_to_memory(char **buf, sscanf_format *arguments, int *rez,
                     char *start) {
  switch (arguments->specifier) {
    case 's':
      skip_blank_spaces(buf);
      write_string(buf, arguments, rez);
      break;

    case 'c':
      write_character(buf, arguments, rez);
      break;

    case 'd':
      skip_blank_spaces(buf);
      write_integer(buf, arguments, rez);
      break;

    case 'i':
      skip_blank_spaces(buf);
      write_i_integer(buf, arguments, rez);
      break;

    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'f':
      skip_blank_spaces(buf);
      write_float(buf, arguments, rez);
      break;

    case 'u':
      skip_blank_spaces(buf);
      write_unsigned(buf, arguments, rez);
      break;
    case 'x':
    case 'X':
    case 'p':
      skip_blank_spaces(buf);
      write_8_16(buf, arguments, rez, 16);
      break;
    case 'o':
      skip_blank_spaces(buf);
      write_8_16(buf, arguments, rez, 8);
      break;
    case 'n':
      *((int *)arguments->adress) = (*buf) - start;
      break;
    default:
      arguments->fail = 1;
  }
}
// Записываем unsigned (спецификатор "u"):

void write_unsigned(char **buf, sscanf_format *arguments, int *rez) {
  arguments->fail = 1;
  int width_flag = arguments->width;
  int i = 0;
  int sign = 1;
  char buffer[BUFF_SIZE] = {'\0'};
  if (s21_strspn(*buf, "0123456789+-")) {
    if (**buf == '-') {
      ++(*buf);
      sign = -1;
      if (arguments->width) {
        --(arguments->width);
      }
    }
    if (**buf == '+') {
      ++(*buf);
      if (arguments->width) {
        --(arguments->width);
      }
    }

    while (**buf && s21_strspn(*buf, "0123456789") != 0) {
      if ((width_flag && i >= arguments->width) ||
          (is_space_enter_tab(**buf))) {
        break;
      }
      arguments->fail = 0;
      buffer[i++] = **buf;
      ++(*buf);
    }
  }

  if (!arguments->fail) {
    unsigned long long int result = sscanf_atoi(buffer);
    if (arguments->asterisk != -1 && !arguments->fail) {
      unsigned_type_converter(arguments, result, sign);
      ++(*rez);
    }
  } else {
    (*buf)--;
  }
}
//  Перевод ASCII во float:

long double sscanf_atof(char **string, sscanf_format *arguments) {
  long double result = 0.0;
  double scale = 1;
  double sign = 1;
  double sign_of_exp = 1;
  double exp_calc = 0;
  double result_with_exp = 0;
  int after_dot = 1;

  while (**string == ' ') {
    ++(*string);
  }

  if (**string == '-') {
    sign = -1;
    ++(*string);
  }

  if (**string == '+') {
    ++(*string);
  }

  if (**string == '.' && arguments->float_stop_rez < 2) {
    arguments->float_stop_rez = 1;
  }

  while (**string != '\0' && **string >= '0' && **string <= '9') {
    result = result * 10 + (**string - '0');
    ++(*string);
  }

  if (**string == '.') {
    ++(*string);
    if (s21_strspn(*string, "0123456789") && arguments->float_stop_rez < 2) {
      arguments->float_stop_rez = 0;
    } else if (arguments->float_stop_rez == 1) {
      arguments->float_stop_rez = 2;
    }
    while (**string != '\0' && **string >= '0' && **string <= '9') {
      scale /= 10;
      result = result + (**string - '0') * scale;
      ++(*string);
      after_dot++;
    }
  }

  if (**string == 'e' || **string == 'E') {
    ++(*string);
    if (**string == '+') {
      ++(*string);
    } else if (**string == '-') {
      sign_of_exp = -1;
      ++(*string);
    }

    while (**string >= '0' && **string <= '9') {
      if (after_dot > 3 && sign_of_exp == -1) {
        result_with_exp = result_with_exp * 10;
        break;
      } else {
        result_with_exp = result_with_exp * 10 + (**string - '0');
        ++(*string);
      }
    }
    exp_calc = exp_calc + result_with_exp * sign_of_exp;
    while (exp_calc > 0) {
      result *= 10;
      --exp_calc;
    }

    while (exp_calc < 0) {
      result /= 10;
      ++exp_calc;
    }
  }
  return result * sign;
}

// Mod atoi:

long long int mod_atoi(char **string, sscanf_format *arguments) {
  long long int result = 0;
  int sign = 1;
  int overflow = 0;
  int width_flag = arguments->width;

  while (**string == ' ') {
    ++(*string);
  }

  if (**string == '-') {
    ++(*string);
    sign = -1;
    --(arguments->width);
  }

  if (**string == '+') {
    ++(*string);
    --(arguments->width);
  }

  if (!(width_flag && arguments->width < 1)) {
    if (arguments->width > 0) {
      for (long int i = 0;
           (i < arguments->width) && (**string >= '0' && **string <= '9');
           i++) {
        result = result * 10 + (**string - '0');
        if (result < 0) {
          overflow = 1;
        }
        (*string)++;
      }
    } else {
      while (**string && **string >= '0' && **string <= '9') {
        result = result * 10 + (**string - '0');
        if (result < 0) {
          overflow = 1;
        }
        (*string)++;
      }
    }
  } else {
    arguments->fail = 1;
  }
  if (overflow)
    result = sign > 0 ? INT32_MAX : INT16_MIN;
  else
    result *= sign;

  return result;
}

//  Проверка символа на пробел/перенос/табуляцию:

int is_space_enter_tab(char symbol) {
  if (symbol == ' ' || symbol == '\n' || symbol == '\t') {
    return 1;
  } else {
    return 0;
  }
}

//  Записываем 8-ричное и 16-ричное

long long int write_8_16(char **buf, sscanf_format *arguments, int *rez,
                         int base) {
  unsigned long long int result = 0;
  int val;
  int flag_pointer = 0;
  char dict[] = "0123456789ABCDEF";
  short exit = 0;
  int sign = 1;
  if (**buf == '-') {
    if (arguments->width) {
      arguments->width--;
    }
    sign = -1;
    (*buf)++;
  } else if (**buf == '+') {
    (*buf)++;
  }
  if (base == 16 && **buf == '0' &&
      (*(*buf + 1) == 'x' || *(*buf + 1) == 'X')) {
    flag_pointer = 1;
    (*buf) += 2;
  }

  if (**buf) {
    if ((s21_strspn(*buf, "0123456789abcdefABCDEF") > 0 ||
         s21_strspn(*buf, "xX0123456789abcdefABCDEF") >= 2)) {
      int i = arguments->width ? arguments->width : (int)s21_strlen(*buf);
      while (**buf != '\0' && i &&
             s21_strspn(*buf, "0123456789abcdefABCDEF") != 0 && !exit) {
        char *tmp2;
        char current_sim =
            (**buf >= 'a' && **buf <= 'z') ? **buf - 'a' + 'A' : **buf;
        tmp2 = s21_strchr(dict, (int)current_sim);
        if (!tmp2) {
          exit = 1;
        } else {
          val = (tmp2 - dict) / sizeof(char);
          if (val >= base) {
            exit = 1;
          } else {
            result = result * base + val;
            (*buf)++;
            i--;
          }
        }
      }

      if (arguments->specifier == 'p' && !exit && arguments->asterisk != -1) {
        *(long int *)arguments->adress = (long int)result;
        (*rez)++;
      } else if (arguments->specifier != 'i' && !exit &&
                 arguments->asterisk != -1) {
        unsigned_type_converter(arguments, result, sign);
        (*rez)++;
      }
    } else {
      arguments->fail = 1;
    }
  } else {
    if (flag_pointer) {
      (*rez)++;

      unsigned_type_converter(arguments, 0, 1);
    } else {
      (*rez)--;
    }
  }
  return result * sign;
}

// Парсинг длины:

const char *sscanf_length(const char *format, sscanf_format *arguments) {
  switch (*format) {
    case 'h':
      arguments->length = 1;
      ++format;
      break;
    case 'l':
      if (*(format + 1) == 'l') {
        arguments->length = LONG_LENGTH;
        format++;
      } else {
        arguments->length = SHORT_LENGTH;
      }
      ++format;
      break;
    case 'L':
      arguments->length = DOUBLE_LENGTH;
      ++format;
      break;
  }
  return format;
}

//  Парсинг ширины:

const char *sscanf_width(const char *format, sscanf_format *arguments) {
  int i = 0;
  char *tmp = NULL;
  if (is_digit(*format)) {
    char tmp[BUFF_SIZE] = {'\0'};
    while (is_digit(*format)) {
      tmp[i] = *format;
      arguments->width = sscanf_atoi(tmp);
      ++i;
      ++format;
    }
  }
  free(tmp);
  return format;
}

// Парсинг флагов:

const char *sscanf_flags(const char *format, sscanf_format *arguments) {
  if (*format == ' ' || *format == '+' || *format == '-' || *format == '*') {
    switch (*format) {
      case '*':
        arguments->asterisk = -1;
        break;
    }
    ++format;
  }
  return format;
}

//  Перевод ASCII в int:

long int sscanf_atoi(const char *string) {
  long int result = 0;
  int overflow = 0;
  int sign = 1;

  while (*string == ' ') {
    ++string;
  }
  if (*string == '-') {
    sign = -1;
    ++string;
  }
  while (is_digit(*string)) {
    result = result * 10 + (*string - '0');
    if (result < 0) {
      overflow = 1;
      break;
    }
    string++;
  }
  if (overflow) {
    if (sign == 1) {
      result = INT_MAX;
    } else {
      result = INT_MIN;
    }
  } else {
    result *= sign;
  }
  return result;
}

//  Проверка строки:

int sscanf_check(const char *string) {
  char tmp[BUFF_SIZE] = {0};
  s21_strcpy(tmp, string);
  int check = -1;
  for (int i = 0; tmp[i] != '\0'; ++i) {
    if (!is_space_enter_tab(tmp[i]) && tmp[i] != '\0') {
      check = 0;
      break;
    }
  }
  return check;
}

// Зануление аругментов строки формата sscanf:

void sscanf_format_zero(sscanf_format *arguments) {
  arguments->width = 0;
  arguments->specifier = 0;
  arguments->length = 0;
  arguments->minus = 0;
  arguments->type = 0;
  arguments->asterisk = 0;
  arguments->plus = 0;
  arguments->space = 0;
}

//  Преобразование типов unsigned:

void unsigned_type_converter(sscanf_format *arguments,
                             unsigned long long int result, int sign) {
  if (arguments->length == FALSE) {
    *(unsigned int *)arguments->adress = sign * (unsigned int)result;
  } else if (arguments->length == TRUE) {
    *(unsigned short int *)arguments->adress =
        sign * (unsigned short int)result;
  } else if (arguments->length == SHORT_LENGTH) {
    *(unsigned long int *)arguments->adress = sign * (unsigned long int)result;
  } else if (arguments->length == LONG_LENGTH) {
    *(unsigned long long int *)arguments->adress =
        sign * (unsigned long long int)result;
  }
}

// Пропуск пустых строк:

void skip_blank_spaces(char **buf) {
  while (is_space_enter_tab(**buf)) {
    ++(*buf);
  }
}

//  Проверка символа на цифру:

int is_digit(char symbol) {
  if (symbol >= '0' && symbol <= '9') {
    return 1;
  } else {
    return 0;
  }
}