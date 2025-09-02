/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:58:26 by secros            #+#    #+#             */
/*   Updated: 2025/09/02 11:05:27 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_struct.h"

#define W 0
#define H 1

static unsigned int	get_color_from_img(t_pict *img, int x, int y)
{
	return (img->addr[y * img->l_size + x * (img->bbp / 8)]);
}

t_color	coord_to_img(t_pict	*map, double u, double v)
{
	const int	x_pix = u * (map->size[W] - 1);
	const int	y_pix = v * (map->size[H] - 1);
	t_color		color;

	color.color = get_color_from_img(map, x_pix, y_pix);
	return (color);
}


