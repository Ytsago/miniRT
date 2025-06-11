/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/06/11 16:58:11 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

#define X 0
#define Y 1
#define Z 2
#include <stdio.h>

// static void	print_vect(void *vect)
// {
// 	t_vect3	print;

// 	print = *((t_vect3 *) vect);
// 	printf("Vect3 : %f, %f, %f\n", print.x, print.y, print.z);
// }
/* 
static void	print_obj(t_object *obj)
{
	t_object	content;

		content = *obj;
		if (content.type == CYLINDER)
			printf("Type : Cylinder\n");
		if (content.type == SPHERE)
			printf("Type : Cylinder\n");
		if (content.type == PLANE)
			printf("Type : Cylinder\n");
		printf("Position : ");
		print_vect(&content.pos);
		printf("\nOrientation : ");
		print_vect(&content.orientation);
		printf("\nSize : ");
		print_vect(&content.size);
		printf("\nColor : RGB : %d, %d, %d\nEND\n",content.color.r, content.color.g, content.color.b);
}
 */
bool	get_value(char **line, void *element)
{
	int		i;
	double	coord[3];
	bool	precision;
	char	*end;

	i = 0;
	while (**line && **line == ' ')
		(*line)++;
	ft_bzero(coord, sizeof(double) * 3);
	while (i < 3 && **line && (ft_isdigit(**line) || ft_issign(**line)))
	{
		// printf("%s\n", *line);
		coord[i] = ft_strtod(*line, &end, &precision);
		if (precision || end == *line)
		{
			if (precision)
				ft_putstr_fd("Error\nPrecision lost...\n", 2);
			return (1);
		}
		*line = end;
		if (**line == ',')
			(*line)++;
		i++;
	}
	*((t_vect3 *) element) = (t_vect3){coord[X], coord[Y], coord[Z]};
	// print_vect(element);
	return (0);
}

bool	get_color(char **line, t_color *color)
{
	unsigned char	rgb[3];
	int				i;

	i = 0;
	while (**line && **line == ' ')
		(*line)++;
	while (i < 3 && **line)
	{
		rgb[i] = ft_atoi(*line);
		while (**line && (ft_isdigit(**line) || ft_issign(**line)))
			(*line)++;
		if (**line == ',')
			(*line)++;
		i++;
	}
	*color = (t_color){.a = 0, .r = rgb[RED], .g = rgb[GREEN], .b = rgb[BLUE]};
	return (0);
}

t_object	*new_object(char **line, enum e_obj type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	ft_bzero(new, sizeof(t_object));
	new->type = type;
	while (**line && !ft_isdigit(**line) && !ft_issign(**line))
	{
		(*line)++;
		// printf("HERE %s\n", *line);
	}
	if (get_value(line, &new->pos))
		return (free(new), NULL);
	// print_vect(&new->pos);
	if (type != SPHERE && get_value(line, &new->orientation))
		return (free(new), NULL);
	// print_vect(&new->orientation);
	if (type != PLANE && get_value(line, &new->size))
		return (free(new), NULL);
	// print_vect(&new->size);
	if (get_color(line, &new->color))
		return (free(new), NULL);
	return ( new);
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
	// printf("%s\n", line);
	if (!ft_strncmp("sp ", line, 3))
		return (add_object(scene, new_object(&line, SPHERE)));
	if (!ft_strncmp("pl ", line, 3))
		return (add_object(scene, new_object(&line, PLANE)));
	if (!ft_strncmp("cy ", line, 3))
		return (add_object(scene, new_object(&line, CYLINDER)));
	return (0);
}
