/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/01 16:31:06 by yabokhar         ###   ########.fr       */
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
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	scene.img[W] = WIDTH;
	scene.img[H] = HEIGHT;
	attribute_threads(&scene, scene.img[W]);
	get_camera(&scene.camera, scene.img);
	get_display_and_new_image(&scene, scene.img);
	debug(&scene);
	rt(&scene);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
		scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
