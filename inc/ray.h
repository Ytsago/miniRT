/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:26:15 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/19 11:38:45 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vect3.h"

typedef struct s_ray
{
	t_vect3	origin;
	t_vect3	direction;
}	t_ray;

t_vect3	ray_at(t_ray r, double t);

#endif
