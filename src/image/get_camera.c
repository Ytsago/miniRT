/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:43:52 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/19 17:28:43 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define W 0
#define H 1
#include "vect3.h"
#include "miniRT.h"
#include "debug.h"

void	get_pixel_zero(t_camera *params)

{
	t_vect3	sum;
	t_vect3 div;

	sum = vect3_add(params->pixel_delta_u, params->pixel_delta_v);
	div = vect3_const_div(sum, 2);
	params->pixel_zero = vect3_add(params->viewport_upper_left, div);
}

void	get_viewport_upper_left(t_camera *params)

{
	const t_vect3	u = vect3_const_div(params->viewport_u, 2);
	const t_vect3	v = vect3_const_div(params->viewport_v, 2);
	const t_vect3	sum = vect3_add(u, v);
	params->viewport_upper_left = vect3_sub(params->prout, vect3_add(sum, params->focal));
}
#include <stdio.h>
void	get_camera(t_camera	*params, short img[2])

{
	const double 	x = (double) (img[W]) / (double) img[H];
	// const double	y = (double) (img[H]) / (double) img[W];

	params->viewport[H] = 2.0;
	params->viewport[W] = params->viewport[H] * x;
	params->focal = (t_vect3){0, 0, 1.0};
	params->prout = (t_vect3){params->view_point[0], params->view_point[1], params->view_point[2]};
	params->viewport_u = (t_vect3){params->viewport[W], 0, 0};
	params->viewport_v = (t_vect3){0, -params->viewport[H], 0};
	params->pixel_delta_u = vect3_const_div(params->viewport_u, img[W]);
	params->pixel_delta_v = vect3_const_div(params->viewport_v, img[H]);
	get_viewport_upper_left(params);
	get_pixel_zero(params);
}
