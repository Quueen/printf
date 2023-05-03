#include "main.h"

/**
 * get_size - Determines the size to cast the argument
 * @format: The formatted string that contains the format specifier
 * @i: A pointer to the current position in the format string
 * Return: The size to cast the argument
 */

int get_size(const char *format, int *i)
{
	int count;
	int size;

	count = *i + 1;
	size = 0;

	if (format[count] == 'l')
	{
		size = S_LONG;
	}
	else if (format[count] == 'h')
	{
		size = S_SHORT;
	}

	if (size == 0)
	{
		*i = count - 1;
	}
	else
	{
		*i = count;
	}

	return (size);
}
