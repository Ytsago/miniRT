/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_shade.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 16:06:16 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/23 17:21:44 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include <math.h>

#define X 0
#define Y 1
#define Z 2
#define R1 30
#define G1 144
#define B1 255
#define R2 248
#define G2 142
#define B2 85

t_color	bg_shade(double direction_y)

{
	t_color		pixel_color;
	float		t;
	float		gradient;

	t = 0.5 * (direction_y + 1.0);
	gradient = (1 - cosf(t * M_PI)) / 2.0f;
	pixel_color.r = (R1 + (R2 - R1) * gradient);
	pixel_color.g = (G1 + (G2 - G1) * gradient);
	pixel_color.b = (B1 + (B2 - B1) * gradient);
	pixel_color.a = 0;
    return (pixel_color);
}
