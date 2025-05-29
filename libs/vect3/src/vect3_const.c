/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_const.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:17:56 by secros            #+#    #+#             */
/*   Updated: 2025/05/26 11:32:14 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

t_vect3	vect3_const_mult(t_vect3 first, double t)
{
	t_vect3	mult;

	mult.x = first.x * t;
	mult.y = first.y * t;
	mult.z = first.z * t;
	return (mult);
}

t_vect3	vect3_const_div(t_vect3 first, double t)
{
	t_vect3	div;

	div.x = first.x / t;
	div.y = first.y / t;
	div.z = first.z / t;
	return (div);
}
