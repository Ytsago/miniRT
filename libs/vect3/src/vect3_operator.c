/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:52:34 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 21:13:23 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

t_vect3	vect3_add(t_vect3 first, t_vect3 second)
{
	return ((t_vect3){{first.coords[X] + second.coords[X], \
first.coords[Y] + second.coords[Y], \
first.coords[Z] + second.coords[Z]}});
}

t_vect3	vect3_sub(t_vect3 first, t_vect3 second)
{
	return ((t_vect3){{first.coords[X] - second.coords[X], \
first.coords[Y] - second.coords[Y], \
first.coords[Z] - second.coords[Z]}});
}

t_vect3	vect3_mult(t_vect3 first, t_vect3 second)
{
	return ((t_vect3){{first.coords[X] * second.coords[X], \
first.coords[Y] * second.coords[Y], \
first.coords[Z] * second.coords[Z]}});
}

t_vect3	vect3_div(t_vect3 first, t_vect3 second)
{
	return ((t_vect3){{first.coords[X] / second.coords[X], \
first.coords[Y] / second.coords[Y], \
first.coords[Z] / second.coords[Z]}});
}

double	vect3_norm(double v[3])
{
	return (sqrt(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
}
