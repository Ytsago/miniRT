/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:43:52 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/26 17:22:21 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define W 0
#define H 1
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

	params->viewport_upper_left = vect3_sub(cam->view_point, vect3_add(sum, cam->focal));
}

void	get_camera(t_camera	*params, short img[2])

{
	t_viewport		*screen;

	screen = &params->viewport;
	screen->viewport[H] = 20;
	screen->viewport[W] = screen->viewport[H] * img[W] / img[H];
	params->focal = (t_vect3){{0, 0, -1}};
	screen->viewport_vect[U] = (t_vect3){{screen->viewport[W], 0, 0}};
	screen->viewport_vect[V] = (t_vect3){{0, -screen->viewport[H], 0}};
	screen->pixel_deltas[U] = vect3_const_div(screen->viewport_vect[U], img[W]);
	screen->pixel_deltas[V] = vect3_const_div(screen->viewport_vect[V], img[H]);
	get_viewport_upper_left(screen, params);
	get_pixel_zero(screen);
}
