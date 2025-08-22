/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 12:36:02 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_int.h"
#include "mlx_struct.h"
#define ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_T 116

void		get_display_and_new_image(t_context *scene, short img[2]);
static bool	get_display(t_context *scene, short img[2]);
static bool	new_image(t_context *scene, short img[2]);

void	get_display_and_new_image(t_context *scene, short img[2])

{
	if (!get_display(scene, img))
	{
		ft_lstclear(&scene->objects, free);
		ft_lstclear(&scene->lights_list, free);
		free(scene->threads);
		exit(1);
	}
	if (!new_image(scene, img))
		mlx_destroy(&scene->screen_ptr);
}

static bool	get_display(t_context *scene, short img[2])
{
	t_mlx	*new;

	new = &scene->screen_ptr;
	ft_fbzero(new, sizeof(t_mlx));
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
		return (false);
	new->win_ptr = mlx_new_window(new->mlx_ptr, img[W], img[H], "miniRT");
	if (!new->win_ptr)
	{
		mlx_destroy_display(new->mlx_ptr);
		free(new->mlx_ptr);
		return (false);
	}
	mlx_hook(new->win_ptr, DestroyNotify, 0, destroy_display, scene);
	return (true);
}

static bool	new_image(t_context *scene, short img[2])
{
	t_mlx	*display;
	t_pict	*new;

	display = &scene->screen_ptr;
	new = &display->img;
	(void)img;
	new->img_ptr = mlx_new_image(display->mlx_ptr, img[W], img[H]);
	if (!new->img_ptr)
		error_failure_from_mlx_new_image(scene, display);
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size, \
		&new->endian);
	if (!new->addr)
	{
		destroy_display(scene);
		return (false);
	}
	return (true);
}

int	handle_key(int keycode, void *params)

{
	t_mlx		*screen;
	t_context	*scene;

	scene = params;
	screen = &scene->screen_ptr;
	if (keycode == ESC)
		destroy_display(scene);
	else if (keycode == KEY_T)
		scene->spectator_mode = !scene->spectator_mode;
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		scene->spectator_mode = true;
		move_camera(&scene->camera, keycode);
		get_camera(&scene->camera, scene->img);
	}
	raytracer(scene);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img.img_ptr, 0, 0);
	return (0);
}
