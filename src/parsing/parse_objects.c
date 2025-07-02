/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/07/02 13:24:53 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>
#include "color.h"
#include "debug.h"
/*
t_object	*new_object(t_context *scene, char **line, enum e_obj type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_object));
	new->type = type;
	(*line) += 3;
	jump_spaces(line);
	if (!get_vect3_value(scene, line, &new->pos))
		return (free(new), NULL);
	if (type != SPHERE && !get_vect3_value(scene, line, &new->orientation))
		return (free(new), NULL);
	jump_spaces(line);
	if ((type == SPHERE && get_unique_value(scene, line, &new->size.coords[X]))
		|| (type == CYLINDER && \
		(get_unique_value(scene, line, &new->size.coords[X])
				|| get_unique_value(scene, line, &new->size.coords[Y]))))
		return (free(new), NULL);
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return (free(new), NULL);
	if (!empty_line(*line))
		return (free(new), write(2, "objects params\n", 14), NULL);
	return (new);
}
*/
void	*free_and_return_null(void *pt)
{
	free(pt);
	return (NULL);
}

t_object	*new_plane(t_context *scene, char **line)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	ft_fbzero(new, sizeof(t_plane));
	new->type = PLANE;
	(*line) += 3;
	jump_spaces(line);
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_vect3_value(scene, line, &new->orientation))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return (free_and_return_null(new));
	return ((t_object *) new);
}

t_object	*new_cylinder(t_context *scene, char **line)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	ft_fbzero(new, sizeof(t_cylinder));
	(*line) += 3;
	jump_spaces(line);
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_vect3_value(scene, line, &new->orientation))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_unique_value(line, &new->diameter))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_unique_value(line, &new->height))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return(free_and_return_null(new));
	return ((t_object *) new);
}

t_object	*new_sphere(t_context *scene, char **line)
{
	t_sphere	*new;
	double		radius;

	new = malloc(sizeof(t_sphere));
	if (!new)
		return (NULL);
	ft_fbzero(new, sizeof(t_sphere));
	new->type = SPHERE;
	(*line) += 3;
	jump_spaces((line));
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (get_unique_value(line, &radius))
		return (free_and_return_null(new));
	new->radius = radius * 0.5;
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return (free_and_return_null(new));
	return ((t_object *) new);
}

bool	add_object(t_context *scene, t_object *object)
{
	t_list	*new;

	if (!object)
		return (false);
	new = ft_lstnew((void *)object);
	if (!new)
	{
		free(object);
		return (false);
	}
	ft_lstadd_back(&scene->objects, new);
	return (true);
}
