/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:05:56 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 19:06:08 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

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
	if (!texture_or_color(scene, (t_object *)new, line))
		return (free_and_return_null(new));
	precalculate_cylinder_values(new);
	return ((t_object *) new);
}
