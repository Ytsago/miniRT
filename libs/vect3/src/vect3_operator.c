/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:52:34 by secros            #+#    #+#             */
/*   Updated: 2025/05/26 11:32:11 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"

t_vect3	vect3_add(t_vect3 first, t_vect3 second)
{
	t_vect3	add;

	add.x = first.x + second.x;
	add.y = first.y + second.y;
	add.z = first.z + second.z;
	return (add);
}

t_vect3	vect3_sub(t_vect3 first, t_vect3 second)
{
	t_vect3	sub;

	sub.x = first.x - second.x;
	sub.y = first.y - second.y;
	sub.z = first.z - second.z;
	return (sub);
}

t_vect3	vect3_mult(t_vect3 first, t_vect3 second)
{
	t_vect3	mult;

	mult.x = first.x * second.x;
	mult.y = first.y * second.y;
	mult.z = first.z * second.z;
	return (mult);
}

t_vect3	vect3_div(t_vect3 first, t_vect3 second)
{
	t_vect3	div;

	div.x = first.x / second.x;
	div.y = first.y / second.y;
	div.z = first.z / second.z;
	return (div);
}

double	vect3_norm(t_vect3 vect)
{
	double	norm;

	norm = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);
	return (norm);
}
