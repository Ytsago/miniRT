/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_at.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:28:26 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 16:17:19 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vect3.h"

t_vect3	ray_at(t_ray r, double t)

{
	return (vect3_add(r.origin, vect3_const_mult(r.direction, t)));
}
