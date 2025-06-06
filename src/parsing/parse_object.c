/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/06/06 16:25:53 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

#define X 0
#define Y 1
#define Z 2

bool	get_value(char **line, void *element)
{
	int		i;
	double	coord[3];
	bool	precision;
	char	*end;

	i = 0;
	ft_bzero(coord, sizeof(double) * 3);
	while (i < 3 && **line && **line != '\n')
	{
		coord[i] = ft_strtod(*line, &end, &precision);
		if (precision || end == *line)
		{
			if (precision)
				ft_putstr_fd("Error\nPrecision lost...\n", 2);
			return (1);
		}
		while (**line && (**line != ',' && **line != ' '))
			(*line)++;
		while (**line && (**line == ' ' || **line == ','))
			(*line)++;
		i++;
	}
	*((t_vect3 *) element) = (t_vect3){coord[X], coord[Y], coord[Z]};
	return (0);
}

static bool	get_color(char **line, t_color *color)
{
	unsigned char	rgb[3];
	int				i;

	i = 0;
	while (i < 3 && **line)
	{
		rgb[i] = ft_atoi(*line);
		while (**line && (ft_isdigit(**line) || ft_issign(**line)))
			(*line)++;
		(*line)++;
		i++;
	}
	*color = (t_color){.a = 0, .r = rgb[RED], .g = rgb[GREEN], .b = rgb[BLUE]};
	return (0);
}

t_object	*new_object(char *line, enum e_obj type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	while (*line && (!ft_isdigit(*line) || *line != '-' || *line != '+'))
		line++;
	if (get_value(&line, &new->pos))
		return (free(new), NULL);
	if (type != SPHERE && get_value(&line, &new->orientation))
		return (free(new), NULL);
	if (get_value(&line, &new->size))
		return (free(new), NULL);
	if (get_color(&line, &new->color))
		return (free(new), NULL);
	return (new);
}

bool	add_object(t_context *scene, t_object *obj)
{
	t_list	*new;

	if (!obj)
		return (1);
	new = ft_lstnew((void *)obj);
	if (!new)
	{
		free(obj);
		return (1);
	}
	ft_lstadd_back(&scene->obj, new);
	return (0);
}

bool	parse_object(char *line, t_context *scene)
{
	if (!ft_strncmp("sp ", line, 3))
		return (add_object(scene, new_object(line, SPHERE)));
	if (!ft_strncmp("pl ", line, 3))
		return (add_object(scene, new_object(line, PLANE)));
	if (!ft_strncmp("cy ", line, 3))
		return (add_object(scene, new_object(line, CYLINDER)));
	return (1);
}
