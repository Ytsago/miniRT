/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:08:22 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/03 21:04:15 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define KEY_S 119
#define KEY_A 97
#define KEY_W 115
#define KEY_D 100
#define KEY_T 116

void	move_camera(t_camera *camera, int keycode)

{
	const double	step = 0.5;
	const t_vect3	up = {{0, 0, 0}};
	t_vect3			right;

	right = vect3_cross(camera->orientation_vector, up);
	if (vect3_norm(right.coords) < 1e-6)
		right = (t_vect3){{1, 0, 0}};
	else
		right = vect3_unit(right);
	if (keycode)
	{
		if (keycode == KEY_W)
			camera->view_point = vect3_add(camera->view_point, \
			vect3_const_mult(camera->orientation_vector, step));
		if (keycode == KEY_S)
			camera->view_point = vect3_sub(camera->view_point, \
			vect3_const_mult(camera->orientation_vector, step));
		if (keycode == KEY_A)
			camera->view_point = vect3_sub(camera->view_point, \
			vect3_const_mult(right, step));
		if (keycode == KEY_D)
			camera->view_point = vect3_add(camera->view_point, \
			vect3_const_mult(right, step));
	}
	camera->orientation_vector = vect3_unit(camera->orientation_vector);
}

#include <stdio.h>

void	move_camera_orientation(t_camera *camera, int mov_x, int mov_y)

{
	(void)camera;
	printf("mov x = %d\n mov y = %d\n", mov_x, mov_y);
}
