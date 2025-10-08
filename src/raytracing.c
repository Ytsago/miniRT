/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:48:44 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/08 14:26:52 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"
#include <stdio.h>

#define W 0
#define H 1
#define U 0
#define V 1
#define IMG_WIDTH 0
#define IMG_HEIGHT 1
#define START_Y 2
#define END_Y 3
#define INDEX_X 4
#define INDEX_Y 5
#define PIXEL_CENTER 0
#define RAY_DIR 1

void			rt(t_context *scene);
static void		*raytracer(void *argument);
static void		get_colors(t_context *scene, int16_t values[6], \
const t_viewport *view, unsigned int *img_ptr);
static short	get_start_y(t_context *scene, short thread_index);

void	rt(t_context *scene)
{
	raytracer(&scene->threads[0]);
}

static void	*raytracer(void *argument)

{
	const t_threads		*thread = (t_threads *)argument;
	const t_context		*scene = thread->scene;
	const t_viewport	*view = (t_viewport *)&scene->camera.viewport;
	int16_t				values[6];

	values[IMG_WIDTH] = scene->img[IMG_WIDTH];
	values[IMG_HEIGHT] = scene->img[IMG_HEIGHT];
	values[START_Y] = get_start_y((t_context *)scene, thread->index);
	values[END_Y] = values[START_Y] + thread->screen_parts[H];
	values[INDEX_X] = -1;
	values[INDEX_Y] = values[START_Y] - 1;
	get_colors((t_context *)scene, values,
		view, (unsigned int *)scene->screen_ptr.img.addr);
	return (NULL);
}

static void	get_colors(t_context *scene, int16_t values[6],
					const t_viewport *view, unsigned int *img_ptr)

{
	t_vect3	pixel_center;
	t_vect3	ray_dir;

	while (++values[INDEX_Y] < values[END_Y])
	{
		values[INDEX_X] = -1;
		while (++values[INDEX_X] < values[IMG_WIDTH])
		{
			pixel_center = vect3_add(view->pixel_zero, vect3_add(
						vect3_const_mult(view->pixel_deltas[U],
							values[INDEX_X]), vect3_const_mult(
							view->pixel_deltas[V], values[INDEX_Y])));
			ray_dir = vect3_unit(vect3_sub(pixel_center,
						scene->camera.view_point));
			img_ptr[values[INDEX_Y] * values[IMG_WIDTH] + values[INDEX_X]]
				= ray_color((t_ray){scene->camera.view_point, ray_dir},
					scene, 4).color;
		}
	}
}

static short	get_start_y(t_context *scene, short thread_index)

{
	short	y;
	short	i;

	y = 0;
	i = 0;
	while (i < thread_index)
	{
		y += scene->threads[i].screen_parts[H];
		i++;
	}
	return (y);
}
