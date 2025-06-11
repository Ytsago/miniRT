/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.PIXELSIZE2.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:00:10 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 18:45:49 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx_int.h"

static void	print_vect(void *vect)
{
	t_vect3	print;

	print = *((t_vect3 *) vect);
	printf("Vect3 : %f, %f, %f", print.x, print.y, print.z);
}

static void	print_obj_lst(t_list *head)
{
	t_object	content;
	int			i;

	i = 0;
	while (head)
	{
		i++;
		content = *((t_object *)head->content);
		printf("%dnd Object -->\n", i);
		if (content.type == CYLINDER)
			printf("Type : Cylinder\n");
		if (content.type == SPHERE)
			printf("Type : sphere\n");
		if (content.type == PLANE)
			printf("Type : plane\n");
		printf("Position : ");
		print_vect(&content.pos);
		printf("\nOrientation : ");
		print_vect(&content.orientation);
		printf("\nSize : ");
		print_vect(&content.size);
		printf("\nColor : RGB : %d, %d, %d\nEND\n\n",content.color.r, content.color.g, content.color.b);
		head = head->next;
	}
}

void	debug_display_scene_param(t_context *scene)
{
	printf("////DEBUG\\\\\\\\\n");
	printf("Ambient light :\nRGB = %d, %d, %d\nRatio :%f\n\n", scene->ambient_lightning.colors[0], scene->ambient_lightning.colors[1], scene->ambient_lightning.colors[2], scene->ambient_lightning.ratio);
	printf("Camera :\nViewpoint : %f, %f, %f,  FOV : %d\nOrientation : ", scene->camera.view_point[0], scene->camera.view_point[1], scene->camera.view_point[2], scene->camera.horizontal_fov);
	print_vect(&scene->camera.orientation_vector);
	printf("\n\nLight :\nBrightness ratio : %f\nPosition : ",scene->light.brightness_ratio);
	print_vect(&scene->light.light_point);
	printf("\nColor : RGB : %d, %d, %d\n\n", scene->light.color.r, scene->light.color.g, scene->light.color.b);
	printf("Obj : \n\n");
	print_obj_lst(scene->obj);
}

int	main(int argc, const char *argv[])
{
	t_context	scene;

	initialize_scene_variables(&scene);
	parse_arguments_then_get_fd(argc, argv, &scene.fd);
	parse_and_load_parameters(&scene);
	debug_display_scene_param(&scene);
}

/* # define PIXELSIZE 4

int colorul_useless_thing(void *data)
{
	int	i[2];
	static unsigned char blue = 255;
	t_display	mlx_display;
	t_color		pixel;
	unsigned int *pixel_ptr;

	blue += 1;
	mlx_display = *(t_display *)data;
	pixel_ptr = (unsigned int *) mlx_display.img.addr;
	ft_bzero(i, sizeof(int) * 2);
	while (i[0] < 256 * PIXELSIZE)
	{
		i[1] = 0;
		while (i[1] < 256 * PIXELSIZE)
		{
			pixel = (t_color){.a = 0, .r = i[1] / PIXELSIZE, .g = i[0] / PIXELSIZE, .b = (blue - (i[0] / 2 + i[1] / 2) / PIXELSIZE)};
			*pixel_ptr = pixel.color;
			pixel_ptr++;
			i[1]++;
		}
		pixel_ptr += (mlx_display.img.l_size / 4) - i[1];
		i[0]++;
	}
	mlx_put_image_to_window(mlx_display.mlx_ptr, mlx_display.win_ptr, mlx_display.img.img_ptr, 0, 0);
	return (0);
}

int	escape(int x, int y, void *data)
{
	t_display	mlx_display;
	mlx_display = *(t_display *)data;
	if (x != 255 || y != 255)
	mlx_mouse_move(mlx_display.mlx_ptr, mlx_display.win_ptr, 255, 255);
	return (0);
}

int	main()
{
	t_display	mlx_display;
	t_color		pixel;
			
	int			i[3];
	ft_bzero(i, sizeof(int) * 2);
	mlx_display.mlx_ptr = mlx_init();
	mlx_display.win_ptr = mlx_new_window(mlx_display.mlx_ptr, 256 * PIXELSIZE, 256 * PIXELSIZE, "color_test");
	mlx_display.img.img_ptr = mlx_new_image(mlx_display.mlx_ptr, 256 * PIXELSIZE, 256 * PIXELSIZE);
	mlx_display.img.addr = mlx_get_data_addr(mlx_display.img.img_ptr, &mlx_display.img.bbp, &mlx_display.img.l_size, &mlx_display.img.endian);
	while (i[0] < 256*PIXELSIZE)
	{
		i[1] = 0;
		while (i[1] < 256*PIXELSIZE)
		{
			pixel = (t_color){.a = 0, .r = i[1] / PIXELSIZE, .g = i[0] / PIXELSIZE, .b = (255 - (i[0] / 2 + i[1] / 2)) / PIXELSIZE};
			*(unsigned int *) (mlx_display.img.addr + (i[0] * mlx_display.img.l_size) + (i[1] * mlx_display.img.bbp >> 3)) = pixel.color;
			i[1]++;
		}
		i[0]++;
	}
	mlx_put_image_to_window(mlx_display.mlx_ptr, mlx_display.win_ptr, mlx_display.img.img_ptr, 0, 0);
	mlx_loop_hook(mlx_display.mlx_ptr, colorul_useless_thing, &mlx_display);
	mlx_hook(mlx_display.win_ptr, MotionNotify, PointerMotionMask, escape, &mlx_display);
	mlx_loop(mlx_display.mlx_ptr);
} */