/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:05:03 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 19:05:43 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	precalculate_cone_values(t_cone *new)
{
	const double	half = new->height / 2;

	new->bot = vect3_sub(new->pos, vect3_const_mult(new->orientation, half));
	new->top = vect3_add(new->pos, vect3_const_mult(new->orientation, half));
	new->k = pow(half, 2) / (pow(half, 2) + pow(new->radius, 2));
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
	if (!texture_or_color(scene, (t_object *)new, line))
		return (free_and_return_null(new));
	precalculate_cone_values(new);
	return ((t_object *) new);
}
