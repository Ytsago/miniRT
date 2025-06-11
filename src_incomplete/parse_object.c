/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 13:35:04 by secros            #+#    #+#             */
/*   Updated: 2025/06/04 15:54:15 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include <stdio.h>

bool	get_object_position(char **line, t_point3 *pos)
{
	while (**line && !ft_isdigit(**line))
	if (!ft_isdigit(**line))
		return (1);
	pos->x = ft_atoi(*line);
	while (**line && **line != ',')
		*line += 1;
	if (!ft_isdigit(**line))
		return (1);
	pos->y = ft_atoi(*line);
	while (**line && **line != ',')
		*line += 1;
	if (!ft_isdigit(**line))
		return (1);
	pos->z = ft_atoi(*line);
	while (**line && !ft_isdigit(**line))
		*line += 1;
	(void) line;
	return (0);
}

static bool	get_colors(short pallet_to_fill[3], char *line)

{
	char	**splitted_line;
	short	index;

	splitted_line = ft_split(line, ',');
	if (!splitted_line)
		return (false);
	index = 0;
	while (splitted_line[index])
		++index;
	if (index != 3)
		return (free_the_mallocs(splitted_line), 0);
	index = 0;
	while (index < 2)
	{
		pallet_to_fill[index] = ft_atoi(splitted_line[index]);
		if (pallet_to_fill[index] < 0 || pallet_to_fill[index] > 255)
			return (free_the_mallocs(splitted_line), 0);
		++index;
	}
	return (free_the_mallocs(splitted_line), 0);
}

static bool	get_ratio(double *ratio, char *line)

{
	const double	integer_part = (double) ft_atoi(line);
	const double	fractional_part = (double) ft_atoi((line + 2));

	if (integer_part != 0.0 && integer_part != 1.0)
		return (false);
	else if (line[1] != '.')
		return (false);
	else if (integer_part == 0.0 && !ft_isdigit(line[2]))
		return (false);
	else if (integer_part == 1 && fractional_part != 0)
		return (false);
	else if (line[3] != ' ')
		return (false);
	*ratio = integer_part + fractional_part / 10;
	return (true);
}

bool	get_object_orientation(char **line, t_vect3 *orientation)
{
	if (!get_ratio(&orientation->x, *line))
		return (1);
	while (**line && **line != ',')
		*line += 1;
	if (!get_ratio(&orientation->x, *line))
		return (1);
	while (**line && **line != ',')
		*line += 1;
	if (!get_ratio(&orientation->x, *line))
		return (1);
	while (**line && **line != ',')
		*line += 1;
	return (0);
}

bool	new_scene_object(t_object obj, t_context *scene)
{
	t_object	*new;
	t_list		*node;

	new = malloc(sizeof(t_object));
	if (!new)
		return (1);
	*new = obj;
	node = ft_lstnew(new);
	if (!node)
		return (free(new), 1);
	ft_lstadd_back(&scene->object_head, node);
	return (0);
}

void	print_t_vect3(t_vect3 vect)
{
	printf("x = %f, y = %f, z = %f", vect.x, vect.y, vect.z);
}

void	print_color(t_color color)
{
	printf("Int : %d, RGB : R = %c, G = %c, B = %c",color.pixel, color.r, color.g, color.b);
}

void	print_object(t_object *obj)
{
	if (obj->type == SPHERE)
		write(1, "Sphere at :", 12);
	if (obj->type == CYLINDER)
		write(1, "Cylinder at :", 14);
	if (obj->type == PLANE)
		write(1, "Plane at :", 11);
	print_t_vect3(obj->pos);
	write(1, "\n Orientation : ", 13);
	print_t_vect3(obj->orientation);
	write(1, "\n Color : ", 11);
	print_color(obj->color);

}

bool	parse_object(char *line,t_context *scene, enum e_geo type)
{
	t_object	object;
	short		color[3];

	printf("%s", line);
	ft_bzero(&object, sizeof(t_object));
	object.type = type;
	if (get_object_position(&line, &object.pos))
		return (1);
	if (type != SPHERE && get_object_orientation(&line, &object.orientation))
		return (1);
	if (get_colors(color, line))
		return (1);
	object.color = (t_color) {.a = 0, .r = color[RED], .g = color[GREEN], .b = color[BLUE]};
	if (new_scene_object(object, scene))
		return (1);
	return (0);
}