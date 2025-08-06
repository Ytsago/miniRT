/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/06 11:36:04 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_int.h"
#include "mlx_struct.h"
# define ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_T 116

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
	}
	raytracer(scene, screen);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img.img_ptr, 0, 0);
	return (0);
}

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
	exit(1);
}

bool	get_display(int height, int width, char *title, t_context* scene)
{
	t_mlx	*new;

	new = &scene->screen_ptr;
	ft_fbzero(new, sizeof(t_mlx));
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
		return (false);
	new->win_ptr = mlx_new_window(new->mlx_ptr, width, height, title);
	if (!new->win_ptr)
	{
		mlx_destroy_display(new->mlx_ptr);
		free(new->mlx_ptr);
		return (false);
	}
	mlx_hook(new->win_ptr, DestroyNotify, 0, destroy_display, scene);
	return (true);
}

bool	new_image(t_mlx *display, int width, int height)
{
	t_pict	*new;

	new = &display->img;
	new->img_ptr = mlx_new_image(display->mlx_ptr, width, height);
	if (!new->img_ptr)
		return (false);
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size, \
		&new->endian);
	if (!new->addr)
	{
		mlx_destroy(display);
		return (false);
	}
	return (true);
}
