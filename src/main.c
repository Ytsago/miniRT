/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/01 14:28:31 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define W 0
#define H 1

int	main(int argc, const char *argv[])
{
	t_context		scene;

	ft_bzero(&scene, sizeof(t_context));
	scene.img[W] = WIDTH;
	scene.img[H] = HEIGHT;
	get_display_and_new_image(&scene, scene.img);
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	attribute_threads(&scene, scene.img[W]);
	get_camera(&scene.camera, scene.img);
	rt(&scene);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
		scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
