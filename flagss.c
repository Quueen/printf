#include "main.h"

/**
 * get_flags - Calculates and returns the active flags
 * @format: The formatted string that contains the format specifier
 * @i: A pointer to the current position in the format string
 * Return: The active flags as an integer value
*/

int get_flags(const char *format, int *i)
{
	int j, count, flags;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	flags = 0;
	for (count = *i + 1; format[count] != '\0'; count++)
	{
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
			if (format[count] == FLAGS_CH[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CH[j] == 0)
			break;
	}

	*i = count - 1;

	return (flags);
}
