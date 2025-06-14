/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 20:55:27 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "../../inc/errors.h"

#define RATIO_ERROR "ambient lightning ratio must be in range [0.0,1.0]\n"
#define OF_ERR "ambient lightning ratio precision lost due to too many digits\n"
#define COLORS_ERROR "ambient lightning colors must be in range [0-255]\n"
#define PARAMS_NUMBER_ERROR "ambient lightning has more than two parameters\n"
#define PRECISION_LOST_ERROR "precision lost (too many digits)\n"

bool			parse_ambient_lightning(char *line, t_context *scene);
static bool		get_ratio(float *ratio, char **line);

bool	parse_ambient_lightning(char *line, t_context *scene)

{
	t_ambient_lightning	*parameters;

	if (scene->element_has_been_declared[AMBIENT_LIGHTNING])
		multiple_declarations_error(scene, "ambient lightning");
	jump_spaces(&line);
	parameters = &scene->ambient_lightning;
	if (!get_ratio(&parameters->ratio, &line))
		return (false);
	jump_spaces(&line);
	if (!get_color(&line, &parameters->color))
		return (false);
	jump_spaces(&line);
	if (*line != '\n' && *line != '\0')
		return (print_error_then_return_false("prout\n"));
	return (true);
}

static bool	get_ratio(float *ratio, char **line)
{
	char	*end;
	bool	precision;

	*ratio = (float) ft_strtod(*line, &end, &precision);
	if (end == *line)
		return (false);
	if (precision)
		return (print_error_then_return_false(OF_ERR));
	if (!(*ratio >= 0.0 && *ratio <= 1.0))
		return (print_error_then_return_false(RATIO_ERROR));
	*line = end;
	if (**line != ' ' )
		return (print_error_then_return_false(NO_SPACE));
	return (true);
}
