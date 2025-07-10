/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 10:47:25 by secros           ###   ########.fr       */
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
	
	screen = ((t_context *)params)->screen_ptr;
	scene = params;
	if (keycode == ESC)
		destroy_display(screen);
	else if (keycode == KEY_T)
		scene->spectator_mode = !scene->spectator_mode;
	else if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_S || keycode == KEY_D)
	{
		scene->spectator_mode = true;
		move_camera(&scene->camera, keycode);
	}
	raytracer(scene, screen);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr, 0, 0);
	return (0);
}

int	destroy_display(t_mlx *display)
{
	mlx_loop_end(display->mlx_ptr);
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	mlx_destroy_display(display->mlx_ptr);
	free(display->mlx_ptr);
	free(display);
	exit(1);
}

t_mlx	*get_display(int height, int width, char *title)
{
	t_mlx	*new;

	new = malloc(sizeof(t_mlx));
	if (!new)
		return (NULL);
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
	{
		free(new);
		return (NULL);
	}
	new->win_ptr = mlx_new_window(new->mlx_ptr, width, height, title);
	if (!new->win_ptr)
	{
		mlx_destroy_display(new->mlx_ptr);
		free(new->mlx_ptr);
		free(new);
		return (NULL);
	}
	mlx_hook(new->win_ptr, DestroyNotify, 0, destroy_display, (void *)new);
	return (new);
}

t_pict	*new_image(t_mlx *display, int width, int height)
{
	t_pict	*new;

	new = malloc(sizeof(t_pict));
	if (!new)
		return (NULL);
	new->img_ptr = mlx_new_image(display->mlx_ptr, width, height);
	if (!new->img_ptr)
	{
		free(new);
		return (NULL);
	}
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size, \
		&new->endian);
	if (!new->addr)
	{
		mlx_destroy_image(display->mlx_ptr, new->img_ptr);
		free(new);
		return (NULL);
	}
	return (new);
}
