/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 08:50:43 by secros           ###   ########.fr       */
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

int	main(int argc, const char *argv[])
{
	t_context		scene;
	t_mlx			*screen;

	ft_bzero(&scene, sizeof(t_context));

	while (argc > 2)
	{	
		int pid = fork();
		if (!pid)
			argv[1] = argv[argc];
		argc--;
	}
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	get_image_dimensions(scene.img);
	get_camera(&scene.camera, scene.img);
	screen = get_display(scene.img[1], scene.img[0], "miniRT");
	screen->img = new_image(screen, scene.img[0], scene.img[1]);

	//Render
	t_vect3		pixel_center;
	t_viewport	*view;

	view = &scene.camera.viewport;
	unsigned int *pixel_ptr = (unsigned int *)screen->img->addr;
	for (int i = 0; i < scene.img[1]; i++)
	{
		ft_printf("Line remaining : %d\n", scene.img[1] - i);
		for (int j = 0; j < scene.img[0]; j++)
		{
			pixel_center = vect3_add(view->pixel_zero, vect3_add(vect3_const_mult(view->pixel_delta_u, j), vect3_const_mult(view->pixel_delta_v, i)));
			t_vect3	ray_dir = vect3_sub(pixel_center, scene.camera.prout);
			t_ray	r = {scene.camera.prout, ray_dir};
			*pixel_ptr = ray_color(r, scene.objects).color;
			pixel_ptr++;
		}
	}
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr, 0, 0);
	//exit(0);

	mlx_loop(screen->mlx_ptr);
	// debug_display_scene_param(&scene);
	// ft_lstclear(&scene.objects, free);
}