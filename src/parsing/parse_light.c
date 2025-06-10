/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:38:43 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/10 18:49:14 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#define MULTIPLE_DECLARATION_ERR3 "light multiple declarations\n"
#define COMMA_ERROR "light point coordinates must be separated by a comma\n"
#define SPACE_ERROR "light parameters must be separated by a space\n"
#define RATIO_ERROR "light ratio must be in range[0.0,1.0]\n"
#define PARAMS_NUMBER_ERROR "light has more than two parameters\n"
#include <stdio.h>

bool		parse_light(char *line, t_context *scene);
static bool	get_light_point_coords(char **line, float point[3], short index);
static bool	get_brightness_ratio(char **line, float *brightness_ratio);

bool	parse_light(char *line, t_context *scene)

{
	t_light	*parameters;

	if (scene->element_has_been_declared[LIGHT])
		return (print_error_then_return_false(MULTIPLE_DECLARATION_ERR3));
	parameters = &scene->light;
	jump_spaces(&line);
	if (!get_light_point_coords(&line, parameters->light_point, 0))
		return (false);
	jump_spaces(&line);
	if (!get_brightness_ratio(&line, &parameters->brightness_ratio))
		return (false);
	jump_spaces(&line);
	if (*line != '\0' && *line != '\n' && *line != ' ')
		return (print_error_then_return_false(PARAMS_NUMBER_ERROR));
	return (true);
}

static bool	get_light_point_coords(char **line, float point[3], short index)

{
	point[index] = atof(*line);
	while (**line == '-')
		++(*line);
	while (ft_isdigit(**line) || **line == '.')
		++(*line);
	if (index < 2 && **line != ',')
		return (print_error_then_return_false(COMMA_ERROR));
	++(*line);
	if (index < 2)
		get_light_point_coords(line, point, ++index);
	if (index == 2 && **line != ' ')
		return (print_error_then_return_false(SPACE_ERROR));
	return (true);
}

static bool	get_brightness_ratio(char **line, float *brightness_ratio)

{
	*brightness_ratio = atof(*line);
	if (*brightness_ratio < 0.0 || *brightness_ratio > 1.0)
		return (print_error_then_return_false(RATIO_ERROR));
	while ((**line >= '0' && **line <= '9') || **line == '.')
		++(*line);
	return (true);
}
