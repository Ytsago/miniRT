/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:00:43 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 18:28:54 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"

#define BOT 0
#define TOP 1
#define EPSILON 1e-4
#define T_MIN 1e-6

t_vect3	cylinder_normal(t_cylinder *cy, t_point3 p)
{
	t_vect3			w;
	double			t2;
	t_vect3			q;

	if (fabs(vect3_scalar(vect3_sub(p, cy->bot), cy->orientation))
		< EPSILON)
		return (vect3_negate(cy->orientation));
	if (fabs(vect3_scalar(vect3_sub(p, cy->top), cy->orientation))
		< EPSILON)
		return (cy->orientation);
	w = vect3_sub(p, cy->pos);
	t2 = vect3_scalar(w, cy->orientation);
	q = vect3_add(cy->pos, vect3_const_mult(cy->orientation, t2));
	return (vect3_unit(vect3_sub(p, q)));
}
