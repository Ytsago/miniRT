/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:08:53 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/01 14:32:49 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "miniRT.h"
#include "mlx_int.h"
#include "mlx_struct.h"

#define W 0
#define H 1
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

t_pict	*load_image(t_mlx *display, char *addr)
{
	t_pict	*new;

	new = ft_calloc(sizeof(t_pict), 1);
	if (!new)
		return (NULL);
	new->img_ptr = mlx_xpm_file_to_image(display->mlx_ptr, addr, \
									  &new->size[W], &new->size[H]);
	if (!new->img_ptr)
		return (free_and_return_null(new));
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size, \
							   &new->endian);
	if (!new->addr)
	{
		mlx_destroy_image(display->mlx_ptr, new->img_ptr);
		return (free_and_return_null(new));
	}
	ft_putendl_fd("Hello", 1);
	return (new);
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
	if (keycode == KEY_T)
		scene->brut_mode = !scene->brut_mode;
	if (keycode == KEY_W || keycode == KEY_A || \
		keycode == KEY_S || keycode == KEY_D)
	{
		move_camera(&scene->camera, keycode);
		get_camera(&scene->camera, scene->img);
	}
	rt(scene);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, \
	screen->img.img_ptr, 0, 0);
	return (0);
}
