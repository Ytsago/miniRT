/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:26:15 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 19:16:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "miniRT.h"
# include "vect3.h"

typedef struct s_ray
{
	t_vect3	origin;
	t_vect3	direction;
}	t_ray;

double	hit_sphere(t_sphere *sp, t_ray ray);
double	hit_plane(t_plane *pl, t_ray ray);
double	hit_cylinder(t_cylinder *cy, t_ray r);
double	hit_cone(t_cone *co, t_ray r);

double	hit_cylinder_caps(t_cylinder *cy, t_ray r);
t_vect3	get_cylinder_normal(t_cylinder *cy, t_ray r, double t);

double	hit_object(t_object *obj, t_ray r);

t_color	ray_color(t_ray dir, t_context *objects, short depth);
t_vect3	ray_at(t_ray r, double t);
t_ray	ray_create(t_vect3 origin, t_vect3 direction);
t_vect3	cylinder_normal(t_cylinder *cy, t_point3 p);
t_vect3	cone_normal(t_cone *co, t_point3 p);

t_vect3	object_normal(t_object *obj, t_vect3 p);

#endif
