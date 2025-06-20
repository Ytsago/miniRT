/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 13:24:23 by secros            #+#    #+#             */
/*   Updated: 2025/06/20 16:26:56 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include "miniRT.h"
#include "color.h"
#include <stdio.h>

void	print_vect(void *vect)
{
	t_vect3	print;
	double	*arr;

	print = *((t_vect3 *) vect);
	arr = print.coords;
	printf("Vect3 : %s%f, %f, %f%s",FG_GREEN, arr[0], arr[1], arr[2], RESET);
}

void	print_obj_lst(t_list *head)
{
	t_object	content;
	int			i;

	i = 0;
	while (head)
	{
		i++;
		content = *((t_object *)head->content);
		printf("%dnd Object -->\n", i);
		if (content.type == CYLINDER)
			printf("Type : Cylinder\n");
		if (content.type == SPHERE)
			printf("Type : sphere\n");
		if (content.type == PLANE)
			printf("Type : plane\n");
		printf("Position : ");
		print_vect(&content.pos);
		printf("\nOrientation : ");
		print_vect(&content.orientation);
		printf("\nSize : ");
		print_vect(&content.size);
		printf("\nColor : RGB : %s%d, %d, %d%s\n\n",FG_RED, content.color.r, content.color.g, content.color.b, RESET);
		head = head->next;
	}
	printf("END\n\n");
}

void	debug_display_scene_param(t_context *scene)
{
	printf("////DEBUG\\\\\\\\\n");
	printf("Ambient light :RGB = %s%d, %d, %d%s\nRatio :%s%f%s\n\n", FG_RED, scene->ambient_lightning.color.r, scene->ambient_lightning.color.g, scene->ambient_lightning.color.b, RESET, FG_GREEN, scene->ambient_lightning.ratio, RESET);
	printf("Camera :\nViewpoint : %s%f, %f, %f%s,  FOV : %s%d%s\nOrientation : ", FG_GREEN, scene->camera.view_point.coords[0], scene->camera.view_point.coords[1], scene->camera.view_point.coords[2], RESET, FG_RED, scene->camera.horizontal_fov, RESET);
	print_vect(&scene->camera.orientation_vector);
	printf("\n\nLight :\nBrightness ratio : %s%f%s\nPosition : ", FG_RED, scene->light.brightness_ratio, RESET);
	print_vect(&scene->light.light_point);
	printf("\nColor : RGB : %s%d, %d, %d%s\n\n", FG_RED, scene->light.color.r, scene->light.color.g, scene->light.color.b, RESET);
	printf("Obj : \n\n");
	print_obj_lst(scene->objects);
}
