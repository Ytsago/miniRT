/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 21:53:41 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/06 21:55:04 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

t_vect3	vect3_rotate(t_vect3 v, t_vect3 axis, double angle)

{
	t_vect3			rot;
	const double	cos = cos(angle);
	const double	sin = sin(angle);

	axis = vect3_unit(axis);
	return (vect3_add(vect3_const_mult(v, cos), \
	vect3_add(vect3_const_mult(vect3_cross(axis, v), sin), \
	vect3_const_mult(axis, vect3_scalar(axis, v) * (1 - cos)))));
}
