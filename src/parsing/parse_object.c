/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/06/12 13:20:55 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>
#include "color.h"

// static void	print_vect(void *vect)
// {
// 	t_vect3	print;

// 	print = *((t_vect3 *) vect);
// 	printf("Vect3 : %s%f, %f, %f%s",FG_GREEN, print.x, print.y, print.z, RESET);
// }

t_object	*new_object(char **line, enum e_obj type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_object));
	new->type = type;
	while (**line && !ft_isdigit(**line) && !ft_issign(**line))
		(*line)++;
	if (get_vect3_value(line, &new->pos))
		return (free(new), NULL);
	if (type != SPHERE && get_vect3_value(line, &new->orientation))
		return (free(new), NULL);
	if ((type == SPHERE && get_unique_value(line, &new->size.x))
		|| (type == CYLINDER && (get_unique_value(line, &new->size.x)
		|| get_unique_value(line, &new->size.y))))
		return (free(new), NULL);
	if (get_color(line, &new->color))
		return (free(new), NULL);
	return (new);
}
#include <stdio.h>
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
		return (add_object(scene, new_object(&line, SPHERE)));
	if (!ft_strncmp("pl ", line, 3))
		return (add_object(scene, new_object(&line, PLANE)));
	if (!ft_strncmp("cy ", line, 3))
		return (add_object(scene, new_object(&line, CYLINDER)));
	return (0);
}
