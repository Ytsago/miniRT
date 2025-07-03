/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:43:13 by secros            #+#    #+#             */
/*   Updated: 2025/07/03 11:56:11 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "../../inc/errors.h"

#define X 0
#define Y 1
#define Z 2

static bool	is_negative(char **line);

bool	get_color(t_context *scene, char **line, t_color *color)
{
	int			rgb[3];
	short		i;
	const bool	negative = is_negative(line);

	i = 0;
	ft_bzero(rgb, sizeof(int) * 3);
	while (i < 3 && **line)
	{
		if (!ft_isdigit(**line) && !ft_issign(**line))
			return (false);
		while (**line >= '0' && **line <= '9')
		{
			rgb[i] = rgb[i] * 10 + **line - '0';
			if (rgb[i] > 255 || negative)
				range_error(scene, "colors", "0", "255");
			++(*line);
		}
		if (i < 2 && verify_and_skip_comma(line))
			no_comma_error(scene);
		i++;
	}
	if (i < 3)
		range_error(scene, "colors", "0", "255");
	*color = (t_color){.a = 0, .r = rgb[RED], .g = rgb[GREEN], .b = rgb[BLUE]};
	return (true);
}

static bool	is_negative(char **line)

{
	bool	answer;

	answer = false;
	while (**line == '+' || **line == '-')
	{
		if (**line == '-')
			answer = !(answer);
		++(*line);
	}
	return (answer);
}

bool	get_unique_value(char **line, double *value)
{
	bool	precision;
	char	*end;

	jump_spaces(line);
	*value = ft_strtod(*line, &end, &precision);
	if (end == *line || precision)
		return (1);
	*line = end;
	return (0);
}

bool	get_vect3_value(t_context *scene, char **line, void *element)
{
	short	i;
	double	coord[3];
	bool	precision;
	char	*end;

	i = 0;
	jump_spaces(line);
	ft_bzero(coord, sizeof(double) * 3);
	precision = false;
	while (i < 3 && **line)
	{
		coord[i] = ft_strtod(*line, &end, &precision);
		if (precision || end == *line)
		{
			if (precision)
				precision_lost_error(scene, "object", "coords");
		}
		*line = end;
		if (i < 2 && verify_and_skip_comma(line))
			no_comma_error(scene);
		i++;
	}
	*((t_vect3 *) element) = (t_vect3){{coord[X], coord[Y], coord[Z]}};
	return (true);
}
