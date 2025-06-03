/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/03 19:53:30 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>

bool			parse_ambient_lightning(char *line, t_context *scene);
static bool		get_ratio(float *ratio, char *line);
static bool		get_colors(unsigned short pallet_to_fill[3], char *line);

bool	parse_ambient_lightning(char *line, t_context *scene)

{
	t_ambient_lightning	*parameters;

	while (*line && *line == ' ')
		++line;
	parameters = &scene->ambient_lightning;
	if (!get_ratio(&parameters->ratio, line))
	{
		write(2, "Error\n", 6);
		write(2, "miniRT: ambient lightning ratio must be in range", 48);
		write(2, " [0.0,1.0]\n", 11);
		return (false);
	}
	line += 3;
	if (!get_colors(parameters->colors, line))
	{
		write(2, "Error\n", 6);
		write(2, "miniRT: ambient lightning colors must be in range", 49);
		write(2, " [0-255]\n", 9);
		return (false);
	}
	return (true);
}

static bool	get_ratio(float *ratio, char *line)

{
	float	integer_part;
	float	fractional_part;

	if (line[0] != '0' && line[0] != '1')
		return (false);
	if (line[1] != '.')
		return (false);
	if (line[0] == '0' && !ft_isdigit(line[2]))
		return (false);
	if (line[0] == '1' && line[2] != '0')
		return (false);
	integer_part = (float)(line[0] - '0');
	fractional_part = (float)((line[2] - '0') / 10.0);
	*ratio = integer_part + fractional_part;
	return (true);
}

static bool	get_colors(unsigned short pallet_to_fill[3], char *line)

{
	pallet_to_fill[RED] = ft_atoi(line);
	if (pallet_to_fill[RED] < 0 || pallet_to_fill[RED] > 255)
		return (false);
	while (*line && *line != ',')
		++line;
	if (!*line)
		return (false);
	pallet_to_fill[GREEN] = ft_atoi(line);
	if (pallet_to_fill[GREEN] < 0 || pallet_to_fill[GREEN] > 255)
		return (false);
	while (*line && *line != ',')
		++line;
	if (!*line)
		return (false);
	pallet_to_fill[BLUE] = ft_atoi(line);
	if (pallet_to_fill[BLUE] < 0 || pallet_to_fill[BLUE] > 255)
		return (false);
	return (true);
}
