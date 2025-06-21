/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_const.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:17:56 by secros            #+#    #+#             */
/*   Updated: 2025/06/21 20:49:38 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

t_vect3	vect3_const_mult(t_vect3 first, double t)
{
	return ((t_vect3){first.coords[X] * t, first.coords[Y] * t,
		first.coords[Z] * t});
}

t_vect3	vect3_const_div(t_vect3 first, double t)
{
	return ((t_vect3){first.coords[X] / t, first.coords[Y] / t,
		first.coords[Z] / t});
}
