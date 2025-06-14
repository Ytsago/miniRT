/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:38:43 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 20:57:03 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "../../inc/errors.h"
#define COMMA_ERROR "light point coordinates must be separated by a comma\n"
#define RATIO_ERROR "light ratio must be in range[0.0,1.0]\n"
#define PRECISION_ERROR "prout\n"
#define PARAMS_NUMBER_ERROR "light has more than two parameters\n"
#define PARAMS_COLOR_ERROR "light color must be in range 0 - 255\n"

bool		parse_light(char *line, t_context *scene);
static bool	get_light_point_coords(char **line, t_point3 *result);
static bool	get_brightness_ratio(char **line, double *brightness_ratio);

bool	parse_light(char *line, t_context *scene)

{
	t_light	*parameters;

	if (scene->element_has_been_declared[LIGHT])
		multiple_declarations_error(scene, "light");
	parameters = &scene->light;
	jump_spaces(&line);
	if (!get_light_point_coords(&line, &parameters->light_point))
		return (false);
	jump_spaces(&line);
	if (!get_brightness_ratio(&line, &parameters->brightness_ratio))
		return (false);
	jump_spaces(&line);
	if (!get_color(&line, &parameters->color))
		return (false);
	jump_spaces(&line);
	if (*line != '\0' && *line != '\n')
		return (print_error_then_return_false(PARAMS_NUMBER_ERROR));
	return (true);
}

static bool	get_light_point_coords(char **line, t_point3 *result)

{
	if (!ft_isdigit(**line) && !ft_issign(**line))
		return (print_error_then_return_false("TRIPLE PROUT\n"));
	if (!get_vect3_value(line, result))
		return (false);
	if (**line != ' ')
		return (print_error_then_return_false(NO_SPACE));
	return (true);
}

static bool	get_brightness_ratio(char **line, double *brightness_ratio)

{
	char	*end;
	bool	precision;

	*brightness_ratio = ft_strtod(*line, &end, &precision);
	if (*line == end)
		return (print_error_then_return_false("double prout\n"));
	if (*brightness_ratio < 0.0 || *brightness_ratio > 1.0)
		return (print_error_then_return_false(RATIO_ERROR));
	if (precision)
		return (print_error_then_return_false(PRECISION_ERROR));
	*line = end;
	if (**line != ' ')
		return (print_error_then_return_false(NO_SPACE));
	return (true);
}
