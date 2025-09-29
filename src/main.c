/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/29 11:55:48 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
		print_obj_lst(scene->objects);
		light = cur->content;
		print_vect(&light->light_point);
		printf("brightness de mes couilles : %f\n", light->brightness_ratio); 
		t_vect3	encule = color_to_vec(light->color);
		print_vect(&encule);
		printf("\n");
		cur = cur->next;
	}
}

void	load_texture(void *pt)
{
	t_object	*obj;

	obj = pt;
	if (!obj->text)
		return ;
	if (!obj->text->img[0])
		obj->color = obj->text->based;
}

void	error_file_loading(char *path)
{
	ft_putstr_fd("Error while loading assets : ", 2);
	ft_putendl_fd(path, 2);
	ft_putendl_fd("Based value used instead...", 2);
}

bool	init_texture(t_vector *v, t_mlx *mlx)
{
	size_t	i;
	t_text	*curr;

	i = 0;
	while (i < v->size)
	{
		curr = vector_get_addr(v, i);
		// printf("Path [0] :%s\nPath[1] : %s\n", curr->path[0], curr->path[1]);
		if (curr->path[0])
		{
			curr->img[0] = load_image(mlx, curr->path[0]);
			if (!curr->img[0])
				error_file_loading(curr->path[0]);
		}
		if (curr->path[1])
		{
			curr->img[1] = load_image(mlx, curr->path[1]);
			if (!curr->img[1])
				error_file_loading(curr->path[1]);
		}
		i++;
	}
	return (true);
}

int	main(int argc, const char *argv[])
{
	t_context		scene;

	ft_bzero(&scene, sizeof(t_context));
	parse_arguments(argc, argv, &scene);
	scene.textures = init_vector(sizeof(t_text));
	parse_and_load_parameters(&scene);
	scene.img[W] = WIDTH;
	scene.img[H] = HEIGHT;
	scene.center_coords[X] = WIDTH >> 1;
	scene.center_coords[Y] = HEIGHT >> 1;
	get_display_and_new_image(&scene, scene.img);
	mlx_mouse_hide(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr);
	mlx_mouse_move(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, scene.img[W] >> 1, scene.img[H] >> 1);
	ft_lstiter(scene.objects, load_texture);
	init_texture(scene.textures, &scene.screen_ptr);
	attribute_threads(&scene, scene.img[W]);
	get_camera(&scene.camera, scene.img);
	// debug(&scene);
	rt(&scene);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
		scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_hook(scene.screen_ptr.win_ptr, 6, 1L << 6, handle_mouse, &scene);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
