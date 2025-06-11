/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/11 17:29:58 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>

#define MULTIPLE_DECLARATION_ERR1 "ambient lightning multiple declarations\n"
#define RATIO_ERROR "ambient lightning ratio must be in range [0.0,1.0]\n"
#define COLORS_ERROR "ambient lightning colors must be in range [0-255]\n"
#define PARAMS_NUMBER_ERROR "ambient lightning has more than two parameters\n"
#define PRECISION_LOST_ERROR "precision lost (too many digits)\n"

bool			parse_ambient_lightning(char *line, t_context *scene);
static bool		get_ratio(float *ratio, char **line);

bool	parse_ambient_lightning(char *line, t_context *scene)

{
	t_ambient_lightning	*parameters;

	if (scene->element_has_been_declared[AMBIENT_LIGHTNING])
		return (print_error_then_return_false(MULTIPLE_DECLARATION_ERR1));
	jump_spaces(&line);
	parameters = &scene->ambient_lightning;
	if (!get_ratio(&parameters->ratio, &line))
		return (false);
	while (ft_isdigit(*line) || *line == '.')
		++line;
	jump_spaces(&line);
	if (get_color(&line, &parameters->color))
		return (print_error_then_return_false(COLORS_ERROR));
	while (ft_isdigit(*line) || *line == ',')
		++line;
	jump_spaces(&line);
	if (*line != '\n' && *line != '\0')
		return (print_error_then_return_false(PARAMS_NUMBER_ERROR));
	return (true);
}

/* static bool	get_ratio(float *ratio, char **line)

{
	*ratio = atof(*line);
	if (*ratio < 0.0 || *ratio > 1.0)
		return (print_error_then_return_false(RATIO_ERROR));
	return (true);
} */


static bool	get_ratio(float *ratio, char **line)
{
	char	*end;
	bool	precision;

	*ratio = (float) ft_strtod(*line, &end, &precision);
	if (end == *line)
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
/* static bool	release_memory_then_return_answer(bool answer, char **array)

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
 */
/* static bool	get_colors(short pallet_to_fill[3], char *line)

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

 */