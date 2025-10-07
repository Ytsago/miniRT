/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:28:46 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 18:27:21 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include "mlx_int.h"

#define W 0
#define H 1

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
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size,
			&new->endian);
	if (!new->addr)
	{
		destroy_display(scene);
		return (false);
	}
	return (true);
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

t_pict	*load_image(t_mlx *display, char *addr)
{
	t_pict	*new;

	new = ft_calloc(sizeof(t_pict), 1);
	if (!new)
		return (NULL);
	new->img_ptr = mlx_xpm_file_to_image(display->mlx_ptr, addr,
			&new->size[W], &new->size[H]);
	if (!new->img_ptr)
		return (free_and_return_null(new));
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size,
			&new->endian);
	if (!new->addr)
	{
		mlx_destroy_image(display->mlx_ptr, new->img_ptr);
		return (free_and_return_null(new));
	}
	return (new);
}
