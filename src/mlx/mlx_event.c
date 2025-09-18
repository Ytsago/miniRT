/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/03 21:06:15 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"
#include "mlx_struct.h"

#define H 0
#define W 1
#define X 0
#define Y 1
#define ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_T 116
#define KEY_B 98

void	mlx_destroy(t_mlx *display)
{
	mlx_loop_end(display->mlx_ptr);
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	mlx_destroy_image(display->mlx_ptr, display->img.img_ptr);
	mlx_destroy_display(display->mlx_ptr);
	free(display->mlx_ptr);
}

int	destroy_display(t_context *scene)
{
	mlx_destroy(&scene->screen_ptr);
	ft_lstclear(&scene->objects, free);
	ft_lstclear(&scene->lights_list, free);
	free(scene->threads);
	exit(1);
}

void	destroy_img(t_pict *img, t_mlx *display)
{
	if (img && img->img_ptr)
		mlx_destroy_image(display->mlx_ptr, img->img_ptr);
	free (img);
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
	if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D)
	{
		move_camera(&scene->camera, keycode);
		get_camera(&scene->camera, scene->img);
	}
	if (keycode == KEY_B)
	{
		print(1, "Time of execution of each thread will be calculated at next frame.\n");
		scene->benchmark = true;
	}
	rt(scene);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, \
	screen->img.img_ptr, 0, 0);
	return (0);
}

int	handle_mouse(int x, int y, void *params)

{
	t_context	*scene;
	t_mlx		*screen;
	int			centers[2];
	int			directions[2];

	scene = params;
	screen = &scene->screen_ptr;
	centers[X] = scene->img[W] >> 1;
	centers[Y] = scene->img[H] >> 1;
	directions[X] = x - centers[X];
	directions[Y] = y - centers[Y];
	if (directions[X] || directions[Y])
	{
		move_camera_orientation(&scene->camera, directions);
		get_camera(&scene->camera, scene->img);
		rt(scene);
		mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img.img_ptr, 0, 0);
		mlx_mouse_move(screen->mlx_ptr, screen->win_ptr, centers[X], centers[Y]);
	}
	return (0);
}
