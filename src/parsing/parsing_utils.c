/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 12:43:13 by secros            #+#    #+#             */
/*   Updated: 2025/06/12 13:21:15 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define X 0
#define Y 1
#define Z 2

void	skip_space(char **line)
{
	while (**line && **line == ' ')
		(*line)++;
}

bool	verify_and_skip_comma(char **line)
{
	if (**line == ',' && (ft_isdigit(*((*line) + 1))
			|| ft_issign(*((*line) + 1))))
	{
		(*line)++;
		return (0);
	}
	else
		return (1);
}

bool	get_color(char **line, t_color *color)
{
	int				rgb[3];
	int				i;

	i = 0;
	skip_space(line);
	ft_bzero(rgb, sizeof(int) * 3);
	while (i < 3 && **line)
	{
		rgb[i] = ft_atoi(*line);
		if (rgb[i] > 255 || rgb[i] < 0)
			return (1);
		while (**line && (ft_isdigit(**line) || ft_issign(**line)))
			(*line)++;
		if (i < 2 && verify_and_skip_comma(line))
			return (1);
		i++;
	}
	if (i < 3)
		return (1);
	*color = (t_color){.a = 0, .r = rgb[RED], .g = rgb[GREEN], .b = rgb[BLUE]};
	return (0);
}

bool	get_unique_value(char **line, double *value)
{
	bool	precision;
	char	*end;

	skip_space(line);
	*value = ft_strtod(*line, &end, &precision);
	if (end == *line || precision)
		return (1);
	*line = end;
	return (0);
}

bool	get_vect3_value(char **line, void *element)
{
	int		i;
	double	coord[3];
	bool	precision;
	char	*end;

	i = 0;
	skip_space(line);
	ft_bzero(coord, sizeof(double) * 3);
	while (i < 3 && **line && (ft_isdigit(**line) || ft_issign(**line)))
	{
		coord[i] = ft_strtod(*line, &end, &precision);
		if (precision || end == *line)
		{
			if (precision)
				ft_putstr_fd("Error\nPrecision lost...\n", 2);
			return (1);
		}
		*line = end;
		if (i < 2 && verify_and_skip_comma(line))
			return (1);
		i++;
	}
	*((t_vect3 *) element) = (t_vect3){coord[X], coord[Y], coord[Z]};
	return (0);
}
