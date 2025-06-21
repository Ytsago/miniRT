/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:32:35 by secros            #+#    #+#             */
/*   Updated: 2025/06/21 14:38:13 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

double	vect3_scalar(t_vect3 first, t_vect3 second)
{
	const double	*f = first.coords;
	const double	*s = second.coords;

	return (f[X] * s[X] + f[Y] * s[Y] + f[Z] * s[Z]);
}

t_vect3	vect3_cross(t_vect3 first, t_vect3 second)
{
	t_vect3	product;
	const double	*f = first.coords;
	const double	*s = second.coords;

	product.coords[X] = f[Y] * s[Z] - f[Z] * s[Y];
	product.coords[Y] = f[Z] * s[X] - f[X] * s[Z];
	product.coords[Z] = f[X] * s[Y] - f[Y]* s[X];
	return (product);
}

t_vect3	vect3_unit(t_vect3 vect)
{
	return (vect3_const_div(vect, vect3_norm(vect)));
}

t_vect3	vect3_negate(t_vect3 v)

{
	return ((t_vect3){-v.coords[X], -v.coords[Y], -v.coords[Z]});
}
