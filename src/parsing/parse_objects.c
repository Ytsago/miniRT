/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/09/04 14:59:19 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>
#include "color.h"
#include "debug.h"
#include "vect3.h"

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
	if (!get_color(scene, line, &new->color))
		return (free_and_return_null(new));
	// new->texture[0] = load_image(&scene->screen_ptr, "./test.xpm");
	new->texture[1] = load_image(&scene->screen_ptr, "./test3_normal.xpm");
	return ((t_object *) new);
}

static void	precalculate_cylinder_values(t_cylinder *new)

{
	t_vect3			orientation;
	const double	half = new->height * 0.5;
	const t_point3	pos = new->pos;

	new->orientation = vect3_unit(new->orientation);
	orientation = new->orientation;
	new->radius *= 0.5;
	new->bot = vect3_sub(pos, vect3_const_mult(orientation, half));
	new->top = vect3_add(pos, vect3_const_mult(orientation, half));
}

t_object	*new_cone(t_context *scene, char **line)
{
	t_cone	*new;

	new = malloc(sizeof(t_cone));
	if (!new)
		return (NULL);
	ft_fbzero(new, sizeof(t_cone));
	new->type = CONE;
	(*line) += 3;
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	if (!get_vect3_value(scene, line, &new->orientation))
		return (free_and_return_null(new));
	new->orientation = vect3_unit(new->orientation);
	if (get_unique_value(line, &new->radius))
		return (free_and_return_null(new));
	new->radius *= 0.5;
	if (get_unique_value(line, &new->height))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return (free_and_return_null(new));
	// precalculate_cone_values(new);
	return ((t_object *) new);
}

t_object	*new_cylinder(t_context *scene, char **line)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		return (NULL);
	ft_fbzero(new, sizeof(t_cylinder));
	new->type = CYLINDER;
	(*line) += 3;
	if (!get_vect3_value(scene, line, &new->pos))
		return (free_and_return_null(new));
	if (!get_vect3_value(scene, line, &new->orientation))
		return (free_and_return_null(new));
	if (get_unique_value(line, &new->radius))
		return (free_and_return_null(new));
	if (get_unique_value(line, &new->height))
		return (free_and_return_null(new));
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return (free_and_return_null(new));
	precalculate_cylinder_values(new);
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
	if (!get_color(scene, line, &new->color))
		return (free_and_return_null(new));
	// new->texture[0] = load_image(&scene->screen_ptr, "./test.xpm");
	// new->texture[1] = load_image(&scene->screen_ptr, "./test3_normal.xpm");
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
