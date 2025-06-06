/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/06 16:13:35 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>

bool			parse_ambient_lightning(char *line, t_context *scene);
static bool		get_ratio(float *ratio, char *line);
static bool		get_colors(short pallet_to_fill[3], char *line);
static bool		release_memory_then_return_answer(bool answer, char **array);

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
	char	*end;
	bool	precision;

	*ratio = (float) ft_strtod((const char *)line, &end, &precision);
	if (end == line)
		return (false);
	if (precision)
	{
		ft_putstr_fd("Error\nPrecision lost due to too many digits\n", 2);
		return (false);
	}
	if (!(*ratio >= 0.0 && *ratio <= 1.0))
		return (false);
	return (true);
}

// static bool	get_ratio(float *ratio, char *line)

// {
// 	const float	integer_part = (float)(line[0] - '0');
// 	const float	fractional_part = (float)((line[2] - '0') / 10);

// 	if (integer_part != 0.0 && integer_part != 1.0)
// 		return (false);
// 	else if (line[1] != '.')
// 		return (false);
// 	else if (integer_part == 0.0 && !ft_isdigit(line[2]))
// 		return (false);
// 	else if (line[2] != '0')
// 		return (false);
// 	else if (line[3] != ' ')
// 		return (false);
// 	*ratio = integer_part + fractional_part;
// 	return (true);
// }

static bool	get_colors(short pallet_to_fill[3], char *line)

{
	char	**splitted_line;
	short	index;

	splitted_line = ft_split(line, ',');
	if (!splitted_line)
		return (false);
	index = 0;
	while (splitted_line[index])
		++index;
	if (index != 3)
		return (release_memory_then_return_answer(false, splitted_line));
	index = 0;
	while (index < 2)
	{
		pallet_to_fill[index] = ft_atoi(splitted_line[index]);
		if (pallet_to_fill[index] < 0 || pallet_to_fill[index] > 255)
			return (release_memory_then_return_answer(false, splitted_line));
		++index;
	}
	return (release_memory_then_return_answer(true, splitted_line));
}

static bool	release_memory_then_return_answer(bool answer, char **array)

{
	size_t	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (answer);
}
