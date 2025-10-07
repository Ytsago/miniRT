/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:43:52 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 20:09:49 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define W 0
#define H 1
#define U 0
#define V 1
#include "vect3.h"
#include "miniRT.h"

void	get_pixel_zero(t_viewport *params)
{
	const t_vect3	sum = vect3_add(params->pixel_deltas[U],
			params->pixel_deltas[V]);
	const t_vect3	div = vect3_const_div(sum, 2);

	params->pixel_zero = vect3_add(params->viewport_upper_left, div);
}

void	get_viewport_upper_left(t_viewport *params, t_camera *cam)
{
	const t_vect3	u = vect3_const_div(params->viewport_vect[U], 2);
	const t_vect3	v = vect3_const_div(params->viewport_vect[V], 2);
	t_vect3			position;

	position = vect3_add(cam->view_point, cam->focal);
	position = vect3_sub(position, v);
	position = vect3_sub(position, u);
	params->viewport_upper_left = position;
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
	const t_vect3	norm_orientation = vect3_unit(params->orientation_vector);
	t_viewport		*screen;
	t_vect3			world_up;
	t_vect3			u;
	t_vect3			v;

	world_up = (t_vect3){{0, 1, 0}};
	screen = &params->viewport;
	screen->viewport[H] = 2;
	screen->viewport[W] = screen->viewport[H] * img[W] / img[H];
	params->focal = get_focal(params->horizontal_fov, screen->viewport[W],
			params->orientation_vector);
	if (fabs(norm_orientation.y) >= 0.999)
		world_up = (t_vect3){{0, 0, 1}};
	u = vect3_unit(vect3_cross(world_up, norm_orientation));
	v = vect3_cross(norm_orientation, u);
	screen->viewport_vect[U] = vect3_const_mult(u, screen->viewport[U]);
	screen->viewport_vect[V] = vect3_const_mult(v, -screen->viewport[V]);
	screen->pixel_deltas[U] = vect3_const_div(screen->viewport_vect[U], img[W]);
	screen->pixel_deltas[V] = vect3_const_div(screen->viewport_vect[V], img[H]);
	get_viewport_upper_left(screen, params);
	get_pixel_zero(screen);
}
