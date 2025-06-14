/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 20:45:01 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx_int.h"
#include "color.h"
#include "debug.h"

int	main(int argc, const char *argv[])
{
	t_context	scene;

	ft_bzero(&scene, sizeof(t_context));
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	debug_display_scene_param(&scene);
	ft_lstclear(&scene.objects, free);
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
