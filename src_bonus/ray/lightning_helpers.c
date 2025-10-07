/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 20:00:34 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 20:03:57 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#define DIFF 0
#define SPEC 1

void	add_reflections(t_vect3 *result, t_vect3 reflections_vectors[2])

{
	*result = vect3_add(*result, reflections_vectors[DIFF]);
	*result = vect3_add(*result, reflections_vectors[SPEC]);
}

void	nullify_vectors(t_vect3 lights_data[3], t_vect3 reflect_vectors[2])

{
	ft_fbzero(reflect_vectors, sizeof(t_vect3) * 2);
	ft_fbzero(lights_data, sizeof(t_vect3) * 3);
}

t_vect3	initial_light(t_ambient_lightning amb_l, t_vect3 obj_color)

{
	return (vect3_mult(\
vect3_const_mult(color_to_vec(amb_l.color), amb_l.ratio), obj_color));
}
