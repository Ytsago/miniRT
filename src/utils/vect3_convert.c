/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_convert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:22:04 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/26 11:39:50 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include "math.h"
#include "mlx_struct.h"

t_vect3	color_to_vec(t_color c)

{
	return ((t_vect3){{c.r / 255.0, c.g / 255.0, c.b / 255.0}});
}

t_color	vec_to_color(t_vect3 v)

{
	t_color	c;

	v.coords[X] = fmin(fmax(v.coords[X], 0.0), 1.0) * 255.99;
	v.coords[Y] = fmin(fmax(v.coords[Y], 0.0), 1.0) * 255.99;
	v.coords[Z] = fmin(fmax(v.coords[Z], 0.0), 1.0) * 255.99;
	c.r = v.coords[X];
	c.g = v.coords[Y];
	c.b = v.coords[Z];
	c.a = 0;
	return (c);
}
