/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/06 11:35:27 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx_int.h"
#include "color.h"
#include "debug.h"
#include "ray.h"

#define WIDTH 720
#define HEIGHT 480
#define W 0
#define H 1
#define U 0
#define V 1
#define SUCCESS 0

void	raytracer(t_context *scene, t_mlx *screen)
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
}

int	main(int argc, const char *argv[])
{
	t_context		scene;

	ft_bzero(&scene, sizeof(t_context));
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	scene.img[W] = WIDTH;
	scene.img[H] = HEIGHT;
	get_camera(&scene.camera, scene.img);
	if (!get_display(scene.img[1], scene.img[0], "miniRT", &scene)
		|| !new_image(&scene.screen_ptr, scene.img[W], scene.img[H]))
	{
		ft_lstclear(&scene.objects, free);
		return (1);
	}
	raytracer(&scene, &scene.screen_ptr);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
		scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
