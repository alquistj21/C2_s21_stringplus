#ifndef C2_S21_STRINGPLUS_2_S21_STRING_H
#define C2_S21_STRINGPLUS_2_S21_STRING_H

#ifndef S21_STRING_S21_STRING_H
#define S21_STRING_S21_STRING_H
#define s21_size_t unsigned long long
#define s21_NULL NULL
#define TOKN_SIGN '%'
#define SPECIFS "cdieEfgGosuxXpn%"
#define TOKN_LENS "hlL"
#define FLAGS "-+ #0"
#define PRECIS_SIGN '.'
#define ADDIT_INT_SIGN '*'
#define DIGITS "0123456789"
#define BASE16LOW "0123456789abcdef"
#define BASE16UP "0123456789ABCDEF"
#define BASE8 "01234567"
#define PTR_LEN 12
#ifdef __APPLE__
#define PTR_NULL_STR ""
#else
#define PTR_NULL_STR "(nil)"
#endif
#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

s21_size_t s21_strlen(const char *str);
s21_size_t s21_strspn(const char *s1, const char *s2);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strerror(int errnum);
char *s21_strdup(const char *str);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
char *s21_strrchr(const char *str, int ch);
char *s21_strchr(const char *str, int c);
int s21_is_delim(char c, const char *delim);
char *s21_strcat(char *dest, const char *src);
char *s21_strcpy(char *dest, const char *src);
void *s21_memset(void *s, int c, s21_size_t n);
char *s21_strtok(char *str, const char *delim);
int s21_strcmp(const char *s1, const char *s2);
// static char* convert_double_to_string(double number, int precision);
void *s21_memchr(const void *s, int c, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
int s21_sprintf(char *out_buf, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);
void *s21_trim(const char *src, const char *trim_chars);
char *s21_strstr(const char *haystack, const char *needle);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
int s21_memcmp(const void *s1, const void *s2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
const char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_insert(const char *src, const char *str, s21_size_t start_index);
void s21_snprintf(char *s, s21_size_t n, const char *format, int errnum,
                  const char *const string);

//    ====SPRINTF+++++++

int s21_sprintf(char *str, const char *format, ...);
// checks if format string has a format specifier
int s21_frmt_is_tokn(const char *format);
// returns pointer to next character after i characters of format
char *s21_tokn_skip_part(const char *format, unsigned int i);
// checks if format string has a given flag character
int s21_tokn_have_flag(const char *format, char flag);
// returns width value specified in format string
int s21_tokn_get_width(const char *format);
// returns precision value specified in format string
int s21_tokn_get_precision(const char *format);
// returns length of string specified in format string
int s21_tokn_get_str_len(const char *format);
// returns length specifier specified in format string
char s21_tokn_get_len(const char *format);
// returns pointer to first occurrence of a given character in string
char *s21_strchr(const char *str, int c);
// returns format specifier character specified in format string
char s21_tokn_get_specif(const char *format);
// writes string representation of unsigned long to str
int s21_trgt_print_ulong(char *str, unsigned long n);
// writes string representation of unsigned long double to str
int s21_trgt_print_uldouble(char *str, long double ld, int precis_len);
// writes string representation of unsigned long double in scientific notation
// to str
int s21_trgt_print_e_uldouble(char *str, long double ld, int precis_len,
                              char e_sign);
// writes string representation of unsigned long in specified base to str
int s21_trgt_print_base_ulong(char *str, unsigned long n, const char *base);
// writes string representation of a character specified in format string to str
int s21_trgt_print_tokn_char(char *str, const char *format, va_list *args);
// writes string representation of a number specified in format string to str
int s21_trgt_print_tokn_num(char *str, const char *format, va_list *args);
// writes string representation of a string specified in format string to str
int s21_trgt_print_tokn_str(char *str, const char *format, va_list *args);
// writes string representation of a ratio (floating-point) specified in format
// string to str
int s21_trgt_print_tokn_ratio(char *str, const char *format, va_list *args);
// writes string representation of a pointer specified in format string to str
int s21_trgt_print_tokn_ptr(char *str, const char *format, va_list *args);
// returns length of string representation of unsigned long in specified base
int s21_base_unum_get_str_len(unsigned long n, char *base);
// returns length of string representation of unsigned long in decimal
int s21_udecim_get_str_len(unsigned long n);
// returns result of raising n to pow
unsigned long s21_ulong_get_pow(unsigned long n, int pow);
// converts string to long
long s21_atol(const char *str);
// returns length of string representation of double in specified precision and
// %e or %f format
int s21_uratio_precis_get_str_len(long double ld, int precis_len);
// returns length of string representation of double in specified precision and
// %E or %F format
int s21_e_uratio_precis_get_str_len(long double ld, int precis_len);
// returns the magnitude of exponent in %e or %E format of double
int s21_e_uratio_get_e(long double ld);

////////////////////SSCANF??????????????????????

#define BUFF_SIZE 5000

enum {
  TRUE = 1,
  FALSE = 0,
  SHORT_LENGTH = -1,
  LONG_LENGTH = 2,
  DOUBLE_LENGTH = 3
};

typedef struct {
  int minus;
  int plus;
  int space;
  int fail;
  int width;
  int asterisk;
  char length;
  char specifier;
  char type;
  void *adress;
  int float_stop_rez;
  int flag_for_i;
} sscanf_format;

int s21_sscanf(const char *src, const char *format, ...);

const char *sscanf_length(const char *format, sscanf_format *arguments);
const char *sscanf_width(const char *format, sscanf_format *arguments);
const char *sscanf_flags(const char *format, sscanf_format *arguments);

void write_string(char **buf, sscanf_format *arguments, int *rez);
void write_character(char **buf, sscanf_format *arguments, int *rez);
void write_integer(char **buf, sscanf_format *arguments, int *rez);
void write_i_integer(char **buf, sscanf_format *arguments, int *rez);
void write_float(char **buf, sscanf_format *arguments, int *rez);
void write_to_memory(char **buf, sscanf_format *arguments, int *rez,
                     char *start);
void write_unsigned(char **buf, sscanf_format *arguments, int *rez);
long long int write_8_16(char **buf, sscanf_format *arguments, int *rez,
                         int base);

long int sscanf_atoi(const char *str);
long double sscanf_atof(char **str, sscanf_format *arguments);
long long int mod_atoi(char **str, sscanf_format *arguments);

void skip_blank_spaces(char **buf);
int is_space_enter_tab(char ch);
int is_digit(char ch);
int sscanf_check(const char *str);
void sscanf_format_zero(sscanf_format *arguments);
void unsigned_type_converter(sscanf_format *arguments,
                             unsigned long long int result, int sign);

#endif  // S21_STRING_S21_STRING_H

#endif  // C2_S21_STRINGPLUS_2_S21_STRING_H
