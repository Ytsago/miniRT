/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:59:44 by secros            #+#    #+#             */
/*   Updated: 2025/10/08 16:58:31 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_struct.h"
#include "vector.h"
#include "miniRT.h"

void	mlx_destroy(t_mlx *display)
{
	mlx_loop_end(display->mlx_ptr);
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	if (display->img.img_ptr)
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
			destroy_img(pt[i].img[0], display);
		if (pt[i].img[1])
			destroy_img(pt[i].img[1], display);
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
