/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 18:28:13 by secros           ###   ########.fr       */
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
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

void	mlx_destroy(t_mlx *display)
{
	mlx_loop_end(display->mlx_ptr);
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	mlx_destroy_image(display->mlx_ptr, display->img.img_ptr);
	mlx_destroy_display(display->mlx_ptr);
	free(display->mlx_ptr);
}

void	clear_texture(t_vector *v, t_mlx *display)
{
	t_text	*pt;
	size_t	i;

	i = 0;
	pt = v->tab;
	while (i < v->size)
	{
		if (pt[i].img[0])
		{
			mlx_destroy_image(display->mlx_ptr, pt[i].img[0]->img_ptr);
			free(pt[i].img[0]);
		}
		if (pt[i].img[1])
		{
			mlx_destroy_image(display->mlx_ptr, pt[i].img[1]->img_ptr);
			free(pt[i].img[1]);
		}
		i++;
	}
	vector_destroy(v);
}

int	destroy_display(t_context *scene)
{
	clear_texture(scene->textures, &scene->screen_ptr);
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

void	handle_this_bullshit(t_context *scene, int keycode)

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
		handle_this_bullshit(scene, keycode);
	rt(scene);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr,
		screen->img.img_ptr, 0, 0);
	return (0);
}
