/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 19:06:33 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "color.h"
#include "vect3.h"

bool	texture_or_color(t_context *scene, t_object *new, char **line)
{
	size_t		id;
	t_vector	*text_list;

	text_list = scene->textures;
	if (**line == 'T' && ft_isdigit(*((*line) + 1)))
	{
		id = ft_atoi(((*line) + 1));
		if (id <= 0 || id > text_list->size)
			return (false);
		new->text = (t_text *)vector_get_addr(scene->textures, id - 1);
	}
	else
	{
		if (!get_color(scene, line, &new->color))
			return (false);
		new->text = NULL;
	}
	return (true);
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
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	if (!get_vect3_value(scene, line, &new->orientation))
		return (free_and_return_null(new));
	new->orientation = vect3_unit(new->orientation);
	jump_spaces(line);
	if (!texture_or_color(scene, (t_object *)new, line))
		return (free_and_return_null(new));
	return ((t_object *) new);
}

t_object	*new_checkerboard(t_context *scene, char **line)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		return (NULL);
	ft_fbzero(new, sizeof(t_plane));
	new->type = CHECKERBOARD;
	(*line) += 3;
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	if (!get_vect3_value(scene, line, &new->orientation))
		return (free_and_return_null(new));
	new->orientation = vect3_unit(new->orientation);
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
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	if (get_unique_value(line, &radius))
		return (free_and_return_null(new));
	new->radius = radius * 0.5;
	jump_spaces(line);
	if (!texture_or_color(scene, (t_object *)new, line))
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
