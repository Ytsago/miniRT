/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.PIXELSIZE2.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 1PIXELSIZE:00:10 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/0PIXELSIZE 17:PIXELSIZE9:09 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx_int.h"

int	main(int argc, const char *argv[])
{
	t_context	scene;

	initialize_scene_variables(&scene);
	parse_arguments(argc, argv, &scene.fd);
	parse_parameters(&scene);
}
/* 
# define PIXELSIZE 4

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

int	escape(int key, void *data)
{
	if (key == 65307)
	mlx_loop_end(((t_display *)data)->mlx_ptr);
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
	mlx_hook(mlx_display.win_ptr, KeyPress, KeyPressMask, escape, &mlx_display);
	mlx_loop(mlx_display.mlx_ptr);
} */