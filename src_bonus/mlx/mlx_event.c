/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/08 16:46:05 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"
#include "mlx_struct.h"

#define H 0
#define W 1

void	handle_camera_orientation(t_context *scene, int keycode)

{
	int	directions[2];

	directions[X] = 0;
	directions[Y] = 0;
	if (keycode == KEY_LEFT)
		directions[X] = 50;
	if (keycode == KEY_RIGHT)
		directions[X] = -50;
	if (keycode == KEY_UP)
		directions[Y] = 50;
	if (keycode == KEY_DOWN)
		directions[Y] = -50;
	move_camera_orientation(&scene->camera, directions);
	get_camera(&scene->camera, scene->img);
}

int	handle_key(int keycode, void *params)
{
	t_mlx		*screen;
	t_context	*scene;

	scene = params;
	screen = &scene->screen_ptr;
	if (keycode == ESC)
		destroy_display(scene);
	if (keycode == KEY_T)
		scene->brut_mode = !scene->brut_mode;
	if (keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D)
	{
		move_camera(&scene->camera, keycode);
		get_camera(&scene->camera, scene->img);
	}
	if (keycode == KEY_UP || keycode == KEY_DOWN
		|| keycode == KEY_LEFT || keycode == KEY_RIGHT)
		handle_camera_orientation(scene, keycode);
	rt(scene);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr,
		screen->img.img_ptr, 0, 0);
	return (0);
}
