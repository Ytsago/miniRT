/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:32:35 by secros            #+#    #+#             */
/*   Updated: 2025/07/02 13:46:11 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include <immintrin.h>
#include <unistd.h>
 
double	vect3_scalar(t_vect3 f, t_vect3 s)
{
	return (f.coords[X] * s.coords[X] + \
		f.coords[Y] * s.coords[Y] + \
		f.coords[Z] * s.coords[Z]);
}

t_vect3	vect3_cross(t_vect3 first, t_vect3 second)
{
	t_vect3			product;
	const double	*f = first.coords;
	const double	*s = second.coords;

	product.coords[X] = f[Y] * s[Z] - f[Z] * s[Y];
	product.coords[Y] = f[Z] * s[X] - f[X] * s[Z];
	product.coords[Z] = f[X] * s[Y] - f[Y] * s[X];
	return (product);
}

t_vect3	vect3_unit(t_vect3 vect)
{
	return (vect3_const_div(vect, vect3_norm(vect.coords)));
}

t_vect3	vect3_negate(t_vect3 v)

{
	return ((t_vect3){{-v.coords[X], -v.coords[Y], -v.coords[Z]}});
}
