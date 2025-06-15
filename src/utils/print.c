/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 20:03:21 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 20:29:52 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#define BUFFER_SIZE 1

void		print(int fd, const char *format, ...);
static void	fill_character(int fd, char *buffer, short *index, char c);
static void	fill_string(int fd, char *buffer, short *index, const char *s);
static void	fill_number(int fd, char *buffer, short *index, int n);
static void	flush_buffer(int fd, char *buffer, short *index);

void	print(int fd, const char *format, ...)
{
	va_list	arguments;
	char	buffer[BUFFER_SIZE];
	short	index;

	index = 0;
	va_start(arguments, format);
	while (*format)
	{
		if (*format == '%')
		{
			++format;
			if (*format == 's')
				fill_string(fd, &buffer[0], &index, va_arg(arguments, char *));
			else if (*format == 'd')
				fill_number(fd, &buffer[0], &index, va_arg(arguments, int));
			else if (*format == 'f')
				write(2, "TODO lol", 8);
		}
		else
			fill_character(fd, &buffer[0], &index, *format);
		format++;
	}
	flush_buffer(fd, &buffer[0], &index);
	va_end(arguments);
}

static void	fill_character(int fd, char *buffer, short *index, char c)

{
	if (*index >= BUFFER_SIZE)
		flush_buffer(fd, buffer, index);
	buffer[(*index)++] = c;
}

static void	fill_string(int fd, char *buffer, short *index, const char *s)

{
	if (!s)
		s = ("(null)");
	while (*s)
		fill_character(fd, buffer, index, *s++);
}

static void	fill_number(int fd, char *buffer, short *index, int n)

{
	short			i;
	char			temporary_buffer[12];
	unsigned int	abs_n;
	const bool		negative = (n < 0);

	i = 11;
	temporary_buffer[i] = '\0';
	if (n == 0)
		temporary_buffer[--i] = '0';
	abs_n = abs(n);
	while (abs_n > 0)
	{
		temporary_buffer[--i] = (abs_n % 10) + '0';
		abs_n /= 10;
	}
	if (negative)
		temporary_buffer[--i] = '-';
	while (temporary_buffer[i])
		fill_character(fd, buffer, index, temporary_buffer[i++]);
}

static void	flush_buffer(int fd, char *buffer, short *index)

{
	if (*index > 0)
	{
		write(fd, buffer, *index);
		*index = 0;
	}
}
