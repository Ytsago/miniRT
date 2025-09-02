/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient_lightning.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:57:00 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/02 11:43:39 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "../../inc/errors.h"

bool			parse_ambient_lightning(char *line, t_context *scene);
static void		get_ratio(t_context *scene, float *ratio, char **line);

bool	parse_ambient_lightning(char *line, t_context *scene)

{
	t_ambient_lightning	*parameters;

	if (scene->element_has_been_declared[AMBIENT_LIGHTNING])
		multiple_declarations_error(scene, "ambient lightning");
	if (*line != ' ' && *line != '\t')
		no_space_error(scene);
	jump_spaces(&line);
	parameters = &scene->ambient_lightning;
	get_ratio(scene, &parameters->ratio, &line);
	if (*line != ' ' && *line != '\t')
		no_space_error(scene);
	jump_spaces(&line);
	if (!get_color(scene, &line, &parameters->color))
		return (false);
	jump_spaces(&line);
	if (*line != '\n' && *line != '\0')
		excessive_params_error(scene, "ambient lightning", '2');
	return (true);
}

static void	get_ratio(t_context *scene, float *ratio, char **line)
{
	char	*end;
	bool	precision;

	*ratio = (float) ft_strtod(*line, &end, &precision);
	if (end == *line)
		range_error(scene, "ambient lightning", "0.0", "1.0");
	if (precision)
		precision_lost_error(scene, "ambient lightning", "ratio");
	if (!(*ratio >= 0.0 && *ratio <= 1.0))
		range_error(scene, "ambient lightning", "0.0", "1.0");
	*line = end;
}
