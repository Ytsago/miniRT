/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/03 20:39:12 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "debug.h"

#define W 0
#define H 1
#include <stdio.h>

void	debug(t_context *scene)

{
	t_list	*cur;
	t_light	*light;

	cur = scene->lights_list;
	while (cur)
	{
		light = cur->content;
		print_vect(&light->light_point);
		printf("brightness de mes couilles : %f\n", light->brightness_ratio); 
		t_vect3	encule = color_to_vec(light->color);
		print_vect(&encule);
		printf("\n");
		cur = cur->next;
	}
}

int	main(int argc, const char *argv[])
{
	t_context		scene;

	ft_bzero(&scene, sizeof(t_context));
	scene.img[W] = WIDTH;
	scene.img[H] = HEIGHT;
	scene.center_coords[X] = WIDTH >> 1;
	scene.center_coords[Y] = HEIGHT >> 1;
	get_display_and_new_image(&scene, scene.img);
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	attribute_threads(&scene, scene.img[W]);
	get_camera(&scene.camera, scene.img);
	debug(&scene);
	rt(&scene);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
		scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_hook(scene.screen_ptr.win_ptr, 6, 1L << 6, handle_mouse, &scene);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
