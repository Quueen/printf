#include "main.h"

/**
 * _printf - a function that produces output according to format and
 * returns number of characters printed.
 * @format: an array of characters
 * Return: number of characters printed.
 */
int _printf(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int count = 0;
	char c;

	for (int i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			write(1, &format[i], 1);
			count++;
		}
		else
		{
			i++;
			if (format[i] == 'c')
			{
				c = va_arg(args, int);
				write(1, &c, 1);
				count++;
			}
			else if (format[i] == 's')
			{
				count += _puts(va_arg(args, char *));
			}
			else if (format[i] == '%')
			{
				write(1, "%", 1);
				count++;
			}
		}
	}
	va_end(args);
	return (count);
}

int _puts(char *str)
{
	int count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		write(1, &str[i], 1);
		count++;
	}
	return (count);
}
