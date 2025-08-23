/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:00:43 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 21:38:19 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"

#define BOT 0
#define TOP 1

t_vect3	cylinder_normal(t_cylinder *cy, t_ray r, double t)

{
	const t_point3	p = ray_at(r, t);
	t_vect3			w;
	double			t2;
	t_vect3			q;

	if (fabs(vect3_scalar(vect3_sub(p, cy->bot), cy->orientation)) \
	< EPSILON)
		return (vect3_negate(cy->orientation));
	if (fabs(vect3_scalar(vect3_sub(p, cy->top), cy->orientation)) \
	< EPSILON)
		return (cy->orientation);
	w = vect3_sub(p, cy->pos);
	t2 = vect3_scalar(w, cy->orientation);
	q = vect3_add(cy->pos, vect3_const_mult(cy->orientation, t2));
	return (vect3_unit(vect3_sub(p, q)));
}
