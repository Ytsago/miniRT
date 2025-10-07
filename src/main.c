/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 17:48:52 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "debug.h"

#define W 0
#define H 1

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
		if (curr->path[0])
		{
			curr->img[0] = load_image(mlx, curr->path[0]);
			free(curr->path[0]);
			if (!curr->img[0])
				error_file_loading(curr->path[0]);
		}
		if (curr->path[1])
		{
			curr->img[1] = load_image(mlx, curr->path[1]);
			free(curr->path[1]);
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
	ft_lstiter(scene.objects, load_texture);
	init_texture(scene.textures, &scene.screen_ptr);
	attribute_threads(&scene, scene.img[W]);
	get_camera(&scene.camera, scene.img);
	rt(&scene);
	mlx_put_image_to_window(scene.screen_ptr.mlx_ptr, scene.screen_ptr.win_ptr, \
scene.screen_ptr.img.img_ptr, 0, 0);
	mlx_key_hook(scene.screen_ptr.win_ptr, handle_key, &scene);
	mlx_loop(scene.screen_ptr.mlx_ptr);
	return (0);
}
