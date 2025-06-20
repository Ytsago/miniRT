/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_const.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:17:56 by secros            #+#    #+#             */
/*   Updated: 2025/06/20 16:12:48 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

t_vect3	vect3_const_mult(t_vect3 first, double t)
{
	t_vect3	mult;

	mult.coords[X] = first.coords[X] * t;
	mult.coords[Y] = first.coords[Y] * t;
	mult.coords[Z] = first.coords[Z] * t;
	return (mult);
}

t_vect3	vect3_const_div(t_vect3 first, double t)
{
	t_vect3	div;

	div.coords[X] = first.coords[X] / t;
	div.coords[Y] = first.coords[Y] / t;
	div.coords[Z] = first.coords[Z] / t;
	return (div);
}
