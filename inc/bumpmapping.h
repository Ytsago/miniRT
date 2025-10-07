/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmapping.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:30:18 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 19:19:09 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUMPMAPPING_H
# define BUMPMAPPING_H

# include "vect3.h"
# include "miniRT.h"

# define U 0
# define V 1
# define EPSILON 1e-4

typedef struct s_tbn	t_tbn;

enum	e_part
{
	MIDDLE,
	TOP,
	BOT,
};

struct s_tbn
{
	t_vect3	normal;
	t_vect3	tangent;
	t_vect3	bitangent;
};

t_vect3	set_area_value(t_object *obj, t_vect3 *normal,
			double value[2], t_tbn matrix);

t_vect3	plane_mapping(t_object *obj, t_point3 p, t_vect3 *normal);
t_vect3	sphere_mapping(t_object *obj, t_point3 p, t_vect3 *normal);
t_vect3	cylinder_mapping(t_cylinder *curr, t_point3 p, t_vect3 *normal);
t_vect3	cone_mapping(t_cone *curr, t_point3 p, t_vect3 *normal);

#endif
