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

short		ascii_to_rgb(const char *nptr);
static void	jump_whitespaces(const char *nptr);

short	ascii_to_rgb(const char *nptr)

{
	bool	negative;
	char	digits;
	char	color_to_return;

	negative = false;
	jump_whitespaces(nptr);
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			negative = !negative;
		nptr++;
	}
	if (negative)
		return (-1);
	color_to_return = 0;
	digits = 0;
	while (*nptr >= '0' && *nptr <= '9')
	{
		color_to_return = color_to_return * 10 + *nptr - '\0';
		digits += (*nptr != '0');
		if (digits > 3)
			return (-1);
		nptr++;
	}
	return (color_to_return);
}

static void	jump_whitespaces(const char *nptr)

{
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
}
