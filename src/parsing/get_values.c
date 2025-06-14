/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:43:13 by secros            #+#    #+#             */
/*   Updated: 2025/06/14 18:00:58 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "../../inc/errors.h"

#define X 0
#define Y 1
#define Z 2
#define COMMA_ERROR "color values must be separated by a comma\n"
#define COLOR_ERROR "ambient lightning colors must be in range [0-255]\n"
#define COLOR_ERR_BIS "ambient lightning colors has less than three colors\n"
#define PRECISION_ERROR "precision lost because of too many digits\n"

bool	get_color(char **line, t_color *color)
{
	int		rgb[3];
	short	i;
	bool	negative;

	i = 0;
	ft_bzero(rgb, sizeof(int) * 3);
	while (i < 3 && **line)
	{
		if (!ft_isdigit(**line) && !ft_issign(**line))
			return (print_error_then_return_false("QUADRUPLE PROUT\n\n"));
		negative = false;
		while (**line == '+' || **line == '-')
		{
			if (**line == '-')
				negative = !(negative);
			++(*line);
		}
		while (**line >= '0' && **line <= '9')
		{
			rgb[i] = rgb[i] * 10 + **line - '0';
			if (rgb[i] > 255 || negative)
				return (print_error_then_return_false(COLOR_ERROR));
			++(*line);
		}
		if (i < 2 && verify_and_skip_comma(line))
			return (print_error_then_return_false(COMMA_ERROR));
		i++;
	}
	if (i < 3)
		return (print_error_then_return_false(COLOR_ERR_BIS));
	*color = (t_color){.a = 0, .r = rgb[RED], .g = rgb[GREEN], .b = rgb[BLUE]};
	return (true);
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

bool	get_vect3_value(char **line, void *element)
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
				return (print_error_then_return_false(PRECISION_ERROR));
		}
		*line = end;
		if (i < 2 && verify_and_skip_comma(line))
			return (print_error_then_return_false(COMMA_ERROR));
		i++;
	}
	*((t_vect3 *) element) = (t_vect3){coord[X], coord[Y], coord[Z]};
	return (true);
}
