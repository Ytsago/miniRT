/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 21:05:06 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#define MULTIPLE_DECLARATION_ERR1 "ambient lightning multiple declarations\n"
#define RATIO_ERROR "ambient lightning ratio must be in range [0.0,1.0]\n"
#define COLORS_ERROR "ambient lightning colors must be in range [0-255]\n"
#define PARAMS_NUMBER_ERROR "ambient lightning has more than two parameters\n"

bool			parse_ambient_lightning(char *line, t_context *scene);
static bool		get_ratio(float *ratio, char *line);

bool	parse_ambient_lightning(char *line, t_context *scene)

{
	t_ambient_lightning	*parameters;

	if (scene->element_has_been_declared[AMBIENT_LIGHTNING])
		return (print_error_then_return_false(MULTIPLE_DECLARATION_ERR1));
	jump_spaces(&line);
	parameters = &scene->ambient_lightning;
	if (!get_ratio(&parameters->ratio, line))
		return (print_error_then_return_false(RATIO_ERROR));
	line += 4;
	jump_spaces(&line);
	if (!fill_pallet(parameters->colors, line))
		return (print_error_then_return_false(COLORS_ERROR));
	while (ft_isdigit(*line) || *line == ',')
		++line;
	jump_spaces(&line);
	if (*line != '\n' && *line != '\0')
		return (print_error_then_return_false(PARAMS_NUMBER_ERROR));
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
