/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:43:52 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 20:25:01 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define W 0
#define H 1
#include "vect3.h"
#include "miniRT.h"

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
	const t_vect3	pos = {params->view_point[0], params->view_point[1], params->view_point[2]};
	const t_vect3	u = vect3_const_div(params->viewport_u, 2);
	const t_vect3	v = vect3_const_div(params->viewport_v, 2);
	const t_vect3	sum = vect3_add(u, v);

	params->viewport_upper_left = vect3_sub(pos, vect3_add(sum, params->focal));
}

void	get_camera(t_camera	*params, short img[2])

{
	const double 	x = img[W] / img[H];
	const double	y = img[H] / img[W];

	params->viewport[W] = 2.0;
	params->viewport[H] = params->viewport[W] * x;
	params->focal = (t_vect3){0, 0, 1.0};
	params->prout = (t_vect3){params->view_point[0], params->view_point[1], params->view_point[2]};
	params->viewport_u = (t_vect3){params->viewport[W], 0, 0};
	params->viewport_v = (t_vect3){0, params->viewport[H] * y * -1, 0};
	params->pixel_delta_u = vect3_const_div(params->viewport_u, img[W]);
	params->pixel_delta_v = vect3_const_div(params->viewport_v, img[H]);
	get_viewport_upper_left(params);
	get_pixel_zero(params);
}
