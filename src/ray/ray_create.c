/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:26:02 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 16:16:31 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vect3.h"

t_ray	ray_create(t_vect3 origin, t_vect3 direction)

{
	t_ray	r;

	r.origin = origin;
	r.direction = direction;
	return (r);
}
