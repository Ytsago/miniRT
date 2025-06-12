/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/06/12 16:18:28 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>
#include "color.h"
#include "debug.h"

t_object	*new_object(char **line, enum e_obj type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_object));
	new->type = type;
	(*line) += 3;
	jump_spaces(line);
	if (!get_vect3_value(line, &new->pos))
		return (free(new), NULL);
	if (type != SPHERE && !get_vect3_value(line, &new->orientation))
		return (free(new), NULL);
	jump_spaces(line);
	if ((type == SPHERE && get_unique_value(line, &new->size.x))
		|| (type == CYLINDER && (get_unique_value(line, &new->size.x)
		|| get_unique_value(line, &new->size.y))))
		return (free(new), NULL);
	jump_spaces(line);
	if (!get_color(line, &new->color))
		return (free(new), NULL);
	if (!empty_line(*line))
		return (free(new), write(2, "objects params\n", 14), NULL);
	return (new);
}
#include <stdio.h>
bool	add_object(t_context *scene, t_object *obj)
{
	t_list	*new;

	if (!obj)
		return (false);
	new = ft_lstnew((void *)obj);
	if (!new)
	{
		free(obj);
		return (false);
	}
	ft_lstadd_back(&scene->obj, new);
	return (true);
}

#include <stdio.h>

bool	parse_object(char *line, t_context *scene)
{
	if (!ft_strncmp("sp ", line, 3))
		return (add_object(scene, new_object(&line, SPHERE)));
	if (!ft_strncmp("pl ", line, 3))
		return (add_object(scene, new_object(&line, PLANE)));
	if (!ft_strncmp("cy ", line, 3))
		return (add_object(scene, new_object(&line, CYLINDER)));
	return (false);
}
