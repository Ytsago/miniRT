/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 10:40:52 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "errors.h" //THIS JUST TO INCLUDE PRINT FAUT QU ON BOUGE
#include "mlx_struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx_int.h"
#include "color.h"
#include "debug.h"
#include "ray.h"
#include <pthread.h>

#define WIDTH 720
#define HEIGHT 480
#define U 0
#define V 1
#define SUCCESS 0

/*void	raytracer(t_context *scene, t_mlx *screen)
{
	int				index[2];
	t_vect3			pixel_center;
	t_vect3			ray_dir;
	t_viewport		*view;
	unsigned int	*pixel_ptr;

	ft_bzero(index, 8);
	pixel_ptr = (unsigned int *)screen->img.addr;
	view = &scene->camera.viewport;
	while (index[Y] < scene->img[H])
	{
		index[X] = 0;
		while (index[X] < scene->img[W])
		{
			pixel_center = vect3_add(view->pixel_zero, \
				vect3_add(vect3_const_mult(view->pixel_deltas[U], index[X]), \
				vect3_const_mult(view->pixel_deltas[V], index[Y])));
			ray_dir = vect3_unit(vect3_sub(pixel_center, scene->camera.view_point));
			*pixel_ptr = ray_color((t_ray){scene->camera.view_point, ray_dir}, scene).color;
			++pixel_ptr;
			++index[X];
		}
		++index[Y];
	}
}*/

#define PIXEL_CENTER 0
#define RAY_DIR 1
#define IMG_H 0
#define IMG_W 1
#define START_Y 2
#define END_Y 3
#define INDEX_X 4
#define INDEX_Y 5

short	get_start_y(t_context *scene, short thread_index)

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

void *multithreaded_raytracer(void *argument)

{
	const t_threads	*thread = (t_threads *)argument;
	t_context		*scene = thread->scene;
	const t_viewport *view = &scene->camera.viewport;
	t_vect3			v[2];
	short			values[6];
	unsigned int	*img;

	values[IMG_H] = scene->img[H];
	values[IMG_W] = scene->img[W];
	values[START_Y] = get_start_y(scene, thread->index);
	values[END_Y] = values[START_Y] + thread->screen_parts[H];
	values[INDEX_X] = 0;
	values[INDEX_Y] = values[START_Y];
	img = (unsigned int *)scene->screen_ptr.img.addr;
	while (values[INDEX_Y] < values[END_Y])
	{
		values[INDEX_X] = 0;
		while (values[INDEX_X] < values[IMG_W])
		{
			v[PIXEL_CENTER] = vect3_add(view->pixel_zero, vect3_add(
					vect3_const_mult(view->pixel_deltas[U], values[INDEX_X]),
					vect3_const_mult(view->pixel_deltas[V], values[INDEX_Y])
				));
			v[RAY_DIR] = vect3_unit(vect3_sub(v[PIXEL_CENTER], scene->camera.view_point));

			img[values[INDEX_Y] * values[IMG_W] + values[INDEX_X]] =
				ray_color((t_ray){scene->camera.view_point, v[RAY_DIR]}, scene).color;

			values[INDEX_X]++;
		}
		values[INDEX_Y]++;
	}
	return (NULL);
}

void	raytracer(t_context *scene, t_mlx *screen)
{
	const long		online_processors = scene->online_processors;
	
	(void)screen;
	for (short i = 0; i < online_processors; i++)
	{
		if (pthread_create(&scene->threads[i].thread, NULL, multithreaded_raytracer, &scene->threads[i]))
			return ;
	}
	for (short i = 0; i < online_processors; i++)
		pthread_join(scene->threads[i].thread, NULL);
	/*short			index[2];
	t_vect3			pixel_center;
	t_vect3			ray_dir;
	t_viewport		*view;
	unsigned int	*pixel_ptr;

	const long		online_processors = scene->online_processors;
	ft_bzero(index, 4);
	view = &scene->camera.viewport;
	pixel_ptr = (unsigned int *)screen->img.addr;
	while (index[Y] < scene->img[H])
	{
		index[X] = 0;
		while (index[X] < scene->img[W])
		{
			pixel_center = vect3_add(view->pixel_zero, \
				vect3_add(vect3_const_mult(view->pixel_deltas[U], index[X]), \
				vect3_const_mult(view->pixel_deltas[V], index[Y])));
			ray_dir = vect3_unit(vect3_sub(pixel_center, scene->camera.view_point));
			*pixel_ptr = ray_color((t_ray){scene->camera.view_point, ray_dir}, scene).color;
			++pixel_ptr;
			++index[X];
		}
		++index[Y];
	}*/
}

int	main(int argc, const char *argv[])
{
	t_context		scene;

	ft_bzero(&scene, sizeof(t_context));
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	scene.img[W] = WIDTH;
	scene.img[H] = HEIGHT;
	if (!attribute_threads(&scene))
		error_malloc_failure_for_threads_array(&scene);
	get_camera(&scene.camera, scene.img);
	if (!get_display(scene.img[1], scene.img[0], "miniRT", &scene)
		|| !new_image(&scene.screen_ptr, scene.img[W], scene.img[H]))
	{
		ft_lstclear(&scene.objects, free);
		free(scene.threads);
		return (1);
	}
	raytracer(&scene, &scene.screen_ptr);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
		scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
