/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 09:02:08 by secros           ###   ########.fr       */
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

#define WIDTH 1920
#define RATIO 1.778
#define W 0
#define H 1

void	raytraycer(t_context *scene, t_mlx *screen)
{
	int				index[2];
	t_vect3			pixel_center;
	t_vect3			ray_dir;
	t_viewport		*view;
	unsigned int	*pixel_ptr;

	ft_bzero(index, 8);
	pixel_ptr = (unsigned int *)screen->img->addr;
	view = &scene->camera.viewport;
	while (index[Y] < scene->img[H])
	{
		index[X] = 0;
		while (index[X] < scene->img[X])
		{
			pixel_center = vect3_add(view->pixel_zero, \
				vect3_add(vect3_const_mult(view->pixel_delta_u, index[X]), \
				vect3_const_mult(view->pixel_delta_v, index[Y])));
			ray_dir = vect3_sub(pixel_center, scene->camera.prout);
			*pixel_ptr = ray_color(\
				(t_ray){scene->camera.prout, ray_dir}, scene->objects).color;
			pixel_ptr++;
			index[X]++;
		}
		index[Y]++;
	}
}

int	main(int argc, const char *argv[])
{
	t_context		scene;
	t_mlx			*screen;

	ft_bzero(&scene, sizeof(t_context));
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	get_image_dimensions(scene.img);
	get_camera(&scene.camera, scene.img);
	screen = get_display(scene.img[1], scene.img[0], "miniRT");
	screen->img = new_image(screen, scene.img[0], scene.img[1]);
	raytraycer(&scene, screen);
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, \
		screen->img->img_ptr, 0, 0);
	mlx_loop(screen->mlx_ptr);
}

// ft_lstclear(&scene.objects, free);