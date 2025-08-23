/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:50:10 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 19:50:14 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "miniRT.h"
#include "vect3.h"

double	hit_plane(t_plane *plane, t_ray ray)

{
	const double	sum = vect3_scalar(plane->orientation, \
		vect3_sub(plane->pos, ray.origin));
	const double	div = vect3_scalar(plane->orientation, ray.direction);
	double			t;

	if (div < EPSILON && div > -EPSILON)
		return (-1);
	t = sum / div;
	if (t < T_MIN)
		return (-1);
	return (t);
}
