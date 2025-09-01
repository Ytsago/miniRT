/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_shade.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:06:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 20:10:04 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include <math.h>

#define R1 30
#define G1 144
#define B1 144
#define R2 255
#define G2 154
#define B2 154

t_color	bg_shade(double direction_y)

{
	const float	gradient = (1 - cosf(0.5 * (direction_y + 1.0) * M_PI)) / 2.5f;

	return ((t_color){.r = (uint8_t)(R1 + (R2 - R1) * gradient), \
	.g = (uint8_t)(G1 + (G2 - G1) * gradient), \
	.b = (uint8_t)(B1 + (B2 - B1) * gradient), \
	.a = (uint8_t)0});
}
