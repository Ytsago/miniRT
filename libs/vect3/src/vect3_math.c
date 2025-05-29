/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:32:35 by secros            #+#    #+#             */
/*   Updated: 2025/05/26 11:32:08 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

double	vect3_scalar(t_vect3 first, t_vect3 second)
{
	double	scalar;

	scalar = first.x * second.x + first.y * second.y + first.z * second.z;
	return (scalar);
}

t_vect3	vect3_cross(t_vect3 first, t_vect3 second)
{
	t_vect3	product;

	product.x = first.y * second.z - first.z * second.y;
	product.y = first.z * second.x - first.x * second.z;
	product.z = first.x * second.y - first.y * second.x;
	return (product);
}

t_vect3	vect3_unit(t_vect3 vect)
{
	return (vect3_const_div(vect, vect3_norm(vect)));
}
