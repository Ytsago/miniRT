/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_to_rgb.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 20:35:33 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 21:05:22 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

short		ascii_to_rgb(char *str, char *offset);
static void	jump_whitespaces(char *str, size_t *c);
static bool	string_represents_a_negative_number(char *str, size_t *c);
static void	jump_zeros(char *str, size_t *c);

short	ascii_to_rgb(char *str, char *offset)

{
	short	color_to_return;
	size_t	character_count;
	char	digits;

	character_count = 0;
	*offset = 0;
	jump_whitespaces(str, &character_count);
	printf("|%s| -> ", str);
	if (string_represents_a_negative_number(str, &character_count))
		return (-1);
	jump_zeros(str, &character_count);
	color_to_return = 0;
	digits = 0;
	while (*str >= '0' && *str <= '9')
	{
		color_to_return = color_to_return * 10 + *str - '0';
		if (++digits > 3)
			return (-1);
		++character_count;
		++str;
	}
	*offset = character_count + digits;
	printf("|%d|\n", color_to_return);
	return (color_to_return);
}

static void	jump_whitespaces(char *str, size_t *count)

{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
	{
		++(*count);
		++str;
	}
}

static bool	string_represents_a_negative_number(char *str, size_t *count)

{
	bool	answer;

	answer = false;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			answer = !answer;
		++str;
		++(*count);
	}
	return (answer);
}

static void	jump_zeros(char *str, size_t *count)

{
	while (*str == '0')
	{
		++str;
		++(*count);
	}
}
