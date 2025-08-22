/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:48:44 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 14:44:33 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "ray.h"
#include <pthread.h>

#define W 0
#define H 1
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
static int16_t	*get_values(const t_context *scene, const t_threads thread);
static short	get_start_y(t_context *scene, short thread_index);

void	rt(t_context *scene)
{
	const long		online_processors = scene->online_processors;
	int8_t			i;

	i = -1;
	while (++i < online_processors)
		if (pthread_create(&scene->threads[i].thread, NULL, raytracer, &scene->threads[i]))
			print(2, "Warning\nminiRT: failed to create thread #%d\n", i);
	i = -1;
	while (++i < online_processors)
		pthread_join(scene->threads[i].thread, NULL);
}

static void	*raytracer(void *argument)

{
	const t_threads		*thread = (t_threads *)argument;
	const t_context		*scene = thread->scene;
	const t_viewport	*view = (t_viewport *)&scene->camera.viewport;
	int16_t				*values;
	t_vect3				v[2];
	unsigned int		*img;

	values = get_values(scene, *thread);
	if (!values)
		return (NULL);
	img = (unsigned int *)scene->screen_ptr.img.addr;
	get_colors(values, view, (unsigned int *)scene->screen_ptr.img.addr);
	return (NULL);
}

static void	get_colors(int16_t *values, const t_viewport *view, unsigned int *img_ptr)

{
	t_vect3	pixel_center;
	t_vect3	ray_dir;

	while (values[INDEX_Y] < values[END_Y])
	{
		values[INDEX_X] = 0;
		while (values[INDEX_X] < values[IMG_WIDTH])
		{
			pixel_center = vect3_add(view->pixel_zero, vect3_add(
					vect3_const_mult(view->pixel_deltas[U], values[INDEX_X]),
					vect3_const_mult(view->pixel_deltas[V], values[INDEX_Y])
				));
			ray_dir = vect3_unit(vect3_sub(v[PIXEL_CENTER], scene->camera.view_point));

			img[values[INDEX_Y] * values[IMG_WIDTH] + values[INDEX_X]] =
				ray_color((t_ray){scene->camera.view_point, ray_dir}, (t_context *)scene).color;

			values[INDEX_X]++;
		}
		values[INDEX_Y]++;
	}
}

static int16_t	*get_values(const t_context *scene, const t_threads thread)

{
	int16_t	*values;

	values = malloc(sizeof(int16_t) * 6);
	if (!values)
		return (NULL);
	values[IMG_WIDTH] = scene->img[IMG_WIDTH];
	values[IMG_HEIGHT] = scene->img[IMG_HEIGHT];
	values[START_Y] = get_start_y((t_context *)scene, thread.index);
	values[END_Y] = values[START_Y] + thread.screen_parts[H];
	values[INDEX_X] = 0;
	values[INDEX_Y] = values[START_Y];
	return (values);
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
