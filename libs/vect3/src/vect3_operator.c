/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:52:34 by secros            #+#    #+#             */
/*   Updated: 2025/06/20 16:25:08 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

t_vect3	vect3_add(t_vect3 first, t_vect3 second)
{
	t_vect3	add;

	add.coords[X] = first.coords[X] + second.coords[X];
	add.coords[Y] = first.coords[Y] + second.coords[Y];
	add.coords[Z] = first.coords[Z] + second.coords[Z];
	return (add);
}

t_vect3	vect3_sub(t_vect3 first, t_vect3 second)
{
	t_vect3	sub;

	sub.coords[X] = first.coords[X] - second.coords[X];
	sub.coords[Y] = first.coords[Y] - second.coords[Y];
	sub.coords[Z] = first.coords[Z] - second.coords[Z];
	return (sub);
}

t_vect3	vect3_mult(t_vect3 first, t_vect3 second)
{
	t_vect3	mult;

	mult.coords[X] = first.coords[X] * second.coords[X];
	mult.coords[Y] = first.coords[Y] * second.coords[Y];
	mult.coords[Z] = first.coords[Z] * second.coords[Z];
	return (mult);
}

t_vect3	vect3_div(t_vect3 first, t_vect3 second)
{
	t_vect3	div;

	div.coords[X] = first.coords[X] / second.coords[X];
	div.coords[Y] = first.coords[Y] / second.coords[Y];
	div.coords[Z] = first.coords[Z] / second.coords[Z];
	return (div);
}

double	vect3_norm(t_vect3 vect)
{
	const double	*v = vect.coords;
	return (sqrt(v[X] * v[X] + v[Y] * v[Y] + v[Z] * v[Z]));
}
