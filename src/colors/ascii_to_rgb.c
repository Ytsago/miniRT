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

short	ascii_to_rgb(const char **str)

{
	short	color_to_return;
	char	digits_count;

	color_to_return = 0;
	digits_count = 0;
	while (**str >= '0' && **str <= '9')
	{
		if (++digits_count > 3)
			return (-1);
		color_to_return = color_to_return * 10 + **str - '0';
		++(*str);
	}
	return (color_to_return);
}
