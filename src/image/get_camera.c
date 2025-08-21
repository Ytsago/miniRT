/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:43:52 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/21 16:25:01 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define U 0
#define V 1
#include "vect3.h"
#include "miniRT.h"
#include "debug.h"

void	get_pixel_zero(t_viewport *params)
{
	const t_vect3	sum = vect3_add(params->pixel_deltas[U], \
	params->pixel_deltas[V]);
	const t_vect3	div = vect3_const_div(sum, 2);

	params->pixel_zero = vect3_add(params->viewport_upper_left, div);
}

void	get_viewport_upper_left(t_viewport *params, t_camera *cam)
{
	const t_vect3	u = vect3_const_div(params->viewport_vect[U], 2);
	const t_vect3	v = vect3_const_div(params->viewport_vect[V], 2);
	const t_vect3	sum = vect3_add(u, v);

	params->viewport_upper_left = vect3_sub(cam->view_point, \
		vect3_add(sum, cam->focal));
}

t_vect3	get_focal(int fov, double size, t_vect3 orientation)
{
	t_vect3			focal;
	const double	demi_lenght = size / 2;
	const double	alpha = (double)(fov) / 2 * M_PI / 180;
	const double	focal_lenght = demi_lenght / tan(alpha);

	ft_fbzero(&focal, sizeof(t_vect3));
	focal = vect3_const_mult(orientation, focal_lenght);
	return (focal);
}

void	get_camera(t_camera	*params, short img[2])
{
	t_viewport		*screen;

	screen = &params->viewport;
	screen->viewport[H] = 2;
	screen->viewport[W] = screen->viewport[H] * img[W] / img[H];
	params->focal = get_focal(params->horizontal_fov, screen->viewport[W], \
		params->orientation_vector);
	screen->viewport_vect[U] = (t_vect3){{screen->viewport[W], 0, 0}};
	screen->viewport_vect[V] = (t_vect3){{0, -screen->viewport[H], 0}};
	screen->pixel_deltas[U] = vect3_const_div(screen->viewport_vect[U], img[W]);
	screen->pixel_deltas[V] = vect3_const_div(screen->viewport_vect[V], img[H]);
	get_viewport_upper_left(screen, params);
	get_pixel_zero(screen);
}
