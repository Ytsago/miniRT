/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:26:15 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/21 15:10:05 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "miniRT.h"
# include "vect3.h"
# include <stdbool.h>

typedef struct s_ray
{
	t_vect3	origin;
	t_vect3	direction;
}	t_ray;

double	hit_sphere(t_point3 pos, double radius, t_ray ray);
t_color	ray_color(t_ray dir, t_context *objects);
t_vect3	ray_at(t_ray r, double t);

#endif
