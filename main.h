#ifndef MAIN_H
#define MAIN_H

#define BUFFSIZE 1024

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * struct form - Struct op
 *
 * @format: data expected
 * @func: the address to the function
 */
struct form
{
	char format;
	int (*func)(va_list, char[], int, int, int, int);
};

int _putchar(char c);
int _printf(const char *format, ...);
int _print_str(va_list args);
int _print_chr(va_list args);
int _print_cent(va_list args);
int _print_int(va_list args);
int _print_dec(va_list args);
int _print_binary(va_list args);
int _print_unsigned(va_list args);
int _print_oct(va_list args);
int _strlen(char *s);
int _strlenc(const char *s);
int _print_hex(va_list args);
int _print_HEX(va_list args);
int _print_excl_str(va_list args);
int _print_ptr(va_list args);
int _print_str_rev(va_list args);
int _print_rot13(va_list args);

#endif
