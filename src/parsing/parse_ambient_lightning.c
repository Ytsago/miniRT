/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 19:19:47 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#define MULTIPLE_DECLARATION_ERROR "ambient lightning multiple declarations\n"
#define RATIO_ERROR "ambient lightning ratio must be in range [0.0,1.0]\n"
#define COLORS_ERROR "ambient lightning colors must be in range [0-255]\n"

bool			parse_ambient_lightning(char *line, t_context *scene);
static bool		get_ratio(float *ratio, char *line);
static bool		get_colors(short pallet_to_fill[3], char *line);
static bool		release_memory_then_return_answer(bool answer, char **array);

bool	parse_ambient_lightning(char *line, t_context *scene)

{
	t_ambient_lightning	*parameters;

	if (scene->element_has_been_declared[AMBIENT_LIGHTNING])
		return (print_error_then_return_false(MULTIPLE_DECLARATION_ERROR));
	while (*line && *line == ' ')
		++line;
	parameters = &scene->ambient_lightning;
	if (!get_ratio(&parameters->ratio, line))
		return (print_error_then_return_false(RATIO_ERROR));
	line += 3;
	if (!get_colors(parameters->colors, line))
		return (print_error_then_return_false(COLORS_ERROR));
	return (true);
}

static bool	get_ratio(float *ratio, char *line)

{
	const float	integer_part = (float)(line[0] - '0');
	const float	fractional_part = (float)((line[2] - '0') / 10);

	if (integer_part != 0.0 && integer_part != 1.0)
		return (false);
	else if (line[1] != '.')
		return (false);
	else if (integer_part == 0.0 && !ft_isdigit(line[2]))
		return (false);
	else if (integer_part == 1.0 && line[2] != '0')
		return (false);
	else if (line[3] != ' ')
		return (false);
	*ratio = integer_part + fractional_part;
	return (true);
}

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
