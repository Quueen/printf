#include "main.h"

/**
 * handle_write_char - Handles the printing of a single character.
 * @c: The character to be printed.
 * @buffer: The buffer array to store the character and padding.
 * @flags: A bitmask that determines which flags are active.
 * @width: The minimum width for the printed character.
 * @precision: The precision specifier (not used in this function).
 * @size: The size specifier (not used in this function).
 * Return: Number of characters printed.
 */

int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	int i;
	char padd;

	i = 0;
	padd = ' ';
	UNUSED(precision);
	UNUSED(size);
	if (flags & F_ZERO)
		padd = '0';
	buffer[i++] = c;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		}
		else
		{
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
		}
	}
	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Handles the printing of a number.
 * @is_negative: Flag indicating whether the number is negative.
 * @ind: The index of the first digit in the buffer array.
 * @buffer: The buffer array containing the digits of the number.
 * @flags: A bitmask that determines which flags are active.
 * @width: The minimum width for the printed number.
 * @precision: The precision specifier (not used in this function).
 * @size: The size specifier (not used in this function).
 * Return: Number of characters printed.
 */

int write_number(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length;
	char padd, extra_ch;

	length = BUFF_SIZE - ind - 1;
	padd = ' ', extra_ch = 0;
	UNUSED(size);
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (is_negative)
	{
		extra_ch = '-';
	}
	else if (flags & F_PLUS)
	{
		extra_ch = '+';
	}
	else if (flags & F_SPACE)
	{
		extra_ch = ' ';
	}

	return (write_num(ind, buffer, flags, width,
				precision, length, padd, extra_ch));
}

/**
 * write_pointer - Writes a memory address to the standard output
 * @buffer: Array of characters to store the address
 * @ind: Index at which the number starts in the buffer
 * @length: Length of the address string
 * @width: Width specifier for the output
 * @flags: Flags specifier for the output
 * @padd: Character representing the padding to be used
 * @extra_c: Character representing any extra character to be added
 * @padd_start: Index at which the padding should start
 * Return: Number of characters written to the standard output.
 */

int write_pointer(char buffer[], int ind, int length,
		int width, int flags, char padd, char extra_c, int padd_start)
{
	int counter;

	if (width > length)
	{
		for (counter = 3; counter < width - length + 3; counter++)
			buffer[counter] = padd;
		buffer[counter] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) +
					write(1, &buffer[3], counter - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], counter - 3) +
					write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], counter - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}

/**
 * write_num - Writes a number to a buffer
 * @ind: Index at which the number starts in the buffer
 * @buffer: Buffer to write to
 * @flags: Flags that control formatting
 * @width: Minimum width of the output
 * @prec: Precision specifier
 * @length: Length of the number
 * @padd: Padding character
 * @extra_c: Extra character to be included in output
 * Return: Number of printed characters.
 */

int write_num(int ind, char buffer[], int flags, int width,
		int prec, int length, char padd, char extra_c)
{
	int counter, padd_start;

	padd_start = 1;
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (counter = 1; counter < width - length + 1; counter++)
			buffer[counter] = padd;
		buffer[counter] = '\0';
		if (flags & F_MINUS && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], counter - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], counter - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], counter - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of written chars.
 */

int write_unsgnd(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size)
{
	int length, counter;
	char padd;

	length = BUFF_SIZE - ind - 1;
	padd = ' ';
	UNUSED(is_negative);
	UNUSED(size);
	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';

	if (width > length)
	{
		counter = 0;
		for (; counter < width - length; counter++)
			buffer[counter] = padd;
		buffer[counter] = '\0';
		if (flags & F_MINUS)
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], counter));
		}
		else
		{
			return (write(1, &buffer[0], counter) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}
