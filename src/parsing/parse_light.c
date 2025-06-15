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

bool		parse_light(char *line, t_context *scene);
static bool	get_light_point_coords(t_context *s, char **line, t_point3 *result);
static bool	get_brightness_ratio(t_context *scene, char **line, double *ratio);

bool	parse_light(char *line, t_context *scene)

{
	t_light	*parameters;

	if (scene->element_has_been_declared[LIGHT])
		multiple_declarations_error(scene, "light");
	parameters = &scene->light;
	jump_spaces(&line);
	if (!get_light_point_coords(scene, &line, &parameters->light_point))
		return (false);
	jump_spaces(&line);
	if (!get_brightness_ratio(scene, &line, &parameters->brightness_ratio))
		return (false);
	jump_spaces(&line);
	if (!get_color(scene, &line, &parameters->color))
		return (false);
	jump_spaces(&line);
	if (*line != '\0' && *line != '\n')
		excessive_params_error(scene, "light", '2');
	return (true);
}

static bool	get_light_point_coords(t_context *s, char **line, t_point3 *result)

{
	if (!ft_isdigit(**line) && !ft_issign(**line))
		return (false);
	if (!get_vect3_value(s, line, result))
		return (false);
	if (**line != ' ')
		no_space_error(s);
	return (true);
}

static bool	get_brightness_ratio(t_context *scene, char **line, double *ratio)

{
	char	*end;
	bool	precision;

	*ratio = ft_strtod(*line, &end, &precision);
	if (*line == end)
		return (false);
	if (*ratio < 0.0 || *ratio > 1.0)
		range_error(scene, "light brightness ratio", "0.0", "1.0");
	if (precision)
		precision_lost_error(scene, "light", "brightness ratio");
	*line = end;
	if (**line != ' ')
		no_space_error(scene);
	return (true);
}
