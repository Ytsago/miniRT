/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:26:15 by yabokhar          #+#    #+#             */
/*   Updated: 2025/07/20 14:10:21 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "miniRT.h"
# include "vect3.h"
# include <stdbool.h>

# define T_MIN		1e-4
# define EPSILON	1e-6

# define DIFF		0
# define SPEC		1

# define N 0
# define M 1
# define T1 0
# define T2 1

enum e_math
{
	A,
	B,
	C,
};

typedef struct s_ray
{
	t_vect3	origin;
	t_vect3	direction;
}	t_ray;

double	hit_sphere(t_sphere *sp, t_ray ray);
double	hit_plane(t_plane *pl, t_ray ray);
double	hit_cylinder(t_cylinder *cy, t_ray r);
double	hit_cylinder_caps(t_cylinder *cy, t_ray r);

t_color	ray_color(t_ray dir, t_context *objects);
t_vect3	ray_at(t_ray r, double t);

#endif
