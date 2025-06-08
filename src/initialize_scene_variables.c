/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_scene_variables.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:09:55 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/03 18:07:40 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	initialize_scene_variables(t_context *scene)

{
	scene->element_has_been_declared[AMBIENT_LIGHTNING] = false;
	scene->element_has_been_declared[CAMERA] = false;
	scene->element_has_been_declared[LIGHT] = false;
	scene->ambient_lightning.ratio = 0.0;
	scene->ambient_lightning.colors[RED] = 0;
	scene->ambient_lightning.colors[GREEN] = 0;
	scene->ambient_lightning.colors[BLUE] = 0;
	scene->camera.view_point[X] = 0.0;
	scene->camera.view_point[Y] = 0.0;
	scene->camera.view_point[Z] = 0.0;
	scene->camera.horizontal_fov = 0;
	scene->light.light_point[X] = 0.0;
	scene->light.light_point[Y] = 0.0;
	scene->light.light_point[Z] = 0.0;
	scene->light.brightness_ratio = 0.0;
}
