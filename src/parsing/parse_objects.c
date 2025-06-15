/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/06/14 15:35:36 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>
#include "color.h"
#include "debug.h"

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
	if ((type == SPHERE && get_unique_value(scene, line, &new->size.x))
		|| (type == CYLINDER && (get_unique_value(scene, line, &new->size.x)
		|| get_unique_value(scene, line, &new->size.y))))
		return (free(new), NULL);
	jump_spaces(line);
	if (!get_color(scene, line, &new->color))
		return (free(new), NULL);
	if (!empty_line(*line))
		return (free(new), write(2, "objects params\n", 14), NULL);
	return (new);
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
