/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 14:38:13 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 16:47:17 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"
#include "libft.h"
#include "ft_printf.h"
#include "mlx_int.h"
#include "color.h"
#include "debug.h"

#define WIDTH 1920
#define RATIO 1.7778


int	destroy_display(t_mlx *display)
{
	mlx_loop_end(display->mlx_ptr);
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	mlx_destroy_display(display->mlx_ptr);
	free(display->mlx_ptr);
	free(display);
	exit(1);
}

t_mlx	*get_display(int height, int width, char *title)
{
	t_mlx	*new;

	new = malloc(sizeof(t_mlx));
	if (!new)
		return (NULL);
	new->mlx_ptr = mlx_init();
	if (!new->mlx_ptr)
	{
		free(new);
		return (NULL);
	}
	new->win_ptr = mlx_new_window(new->mlx_ptr, width, height, title);
	if (!new->win_ptr)
	{
		mlx_destroy_display(new->mlx_ptr);
		free(new->mlx_ptr);
		free(new);
		return (NULL);
	}
	mlx_hook(new->win_ptr, DestroyNotify, 0, destroy_display, (void *)new);
	return (new);
}

t_pict	*new_image(t_mlx *display, int width, int height)
{
	t_pict	*new;

	new = malloc(sizeof(t_pict));
	if (!new)
		return (NULL);
	new->img_ptr = mlx_new_image(display->mlx_ptr, width, height);
	if (!new->img_ptr)
	{
		free(new);
		return (NULL);
	}
	new->addr = mlx_get_data_addr(new->img_ptr, &new->bbp, &new->l_size, &new->endian);
	if (!new->addr)
	{
		mlx_destroy_image(display->mlx_ptr, new->img_ptr);
		free(new);
		return (NULL);
	}
	return (new);
}

t_color ray_color(t_vect3 dir)
{
    t_vect3	unit_direction = vect3_unit(dir);
    double	a = 0.5*(unit_direction.y + 1.0);
	t_vect3	rgb = vect3_add(vect3_const_mult(((t_vect3) {1.0, 1.0, 1.0}), (1.0-a)), vect3_const_mult(((t_vect3) {0.5, 0.7, 1.0}), a));
	return ((t_color) {.r = rgb.x * 255.99 , .g = rgb.y * 255.99, .b = rgb.z * 255.99, .a = rgb.z * 255.99});
}

int	main(int argc, const char *argv[])
{
	t_context		scene;
	t_mlx			*screen;

	//Image
	const int		img_width = WIDTH;
	const int		img_height = WIDTH / RATIO;

	//Camera
	const double	viewport_height = 2.0;
	const double	viewport_width = viewport_height * (double)(img_width / img_height);
	const t_vect3	camera_center = {0, 0, 0};
	const double	focal_lenght = 1.0;

	//Vector accross the viewport
	const t_vect3	viewport_u = {viewport_width, 0, 0};
	const t_vect3	viewport_v = {0, -viewport_height, 0};

	//Delta for vector
	const t_vect3	pixel_delta_u = vect3_const_div(viewport_u, img_width);
	const t_vect3	pixel_delta_v = vect3_const_div(viewport_v, img_height);

	//Upper left pixel
	const t_vect3	viewport_upper_left = vect3_sub(camera_center, vect3_add(vect3_add(vect3_const_div(viewport_v, 2), vect3_const_div(viewport_u, 2)), ((t_vect3) {0, 0, focal_lenght})));
	const t_vect3	pixel_zero = vect3_add(viewport_upper_left, vect3_const_div(vect3_add(pixel_delta_u, pixel_delta_v), 2));
	
	ft_bzero(&scene, sizeof(t_context));
	parse_arguments(argc, argv, &scene);
	parse_and_load_parameters(&scene);
	screen = get_display(img_height, img_width, "HELLO WORLD");
	screen->img = new_image(screen, img_width, img_height);

	//Render
	t_vect3	pixel_center;
	unsigned int *pixel_ptr = (unsigned int *)screen->img->addr;
	for (int i = 0; i < img_height; i++)
	{
		ft_printf("Line remaining : %d\n", img_height - i);
		for (int j = 0; j < img_width; j++)
		{
			pixel_center = vect3_add(pixel_zero, vect3_add(vect3_const_mult(pixel_delta_u, j), vect3_const_mult(pixel_delta_v, i)));
			t_vect3	ray_dir = vect3_sub(pixel_center, camera_center);
			*pixel_ptr = ray_color(ray_dir).color;
			pixel_ptr++;
		}
	}
	mlx_put_image_to_window(screen->mlx_ptr, screen->win_ptr, screen->img->img_ptr, 0, 0);

	mlx_loop(screen->mlx_ptr);
	// debug_display_scene_param(&scene);
	// ft_lstclear(&scene.objects, free);
}

//  # define PIXELSIZE 1

/* int colorul_useless_thing(void *data)
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
	ft_bzero(i, sizeof(int) * 3);
	mlx_display.mlx_ptr = mlx_init();
	mlx_display.win_ptr = mlx_new_window(mlx_display.mlx_ptr, 256 * PIXELSIZE, 256 * PIXELSIZE, "color_test");
	mlx_display.img.img_ptr = mlx_new_image(mlx_display.mlx_ptr, 256 * PIXELSIZE, 256 * PIXELSIZE);
	mlx_display.img.addr = mlx_get_data_addr(mlx_display.img.img_ptr, &mlx_display.img.bbp, &mlx_display.img.l_size, &mlx_display.img.endian);
	while (i[0] < 256*PIXELSIZE)
	{
		i[1] = 0;
		while (i[1] < 256*PIXELSIZE)
		{
			pixel = (t_color){.a = 0, .r = i[1] / PIXELSIZE, .g = i[0] / PIXELSIZE, .b = (255 - (i[0] >> 1 + i[1] / 2)) / PIXELSIZE};
			*(unsigned int *) (mlx_display.img.addr + (i[0] * mlx_display.img.l_size) + (i[1] * mlx_display.img.bbp >> 3)) = pixel.color;
			i[1]++;
		}
		i[0]++;
	}
	mlx_put_image_to_window(mlx_display.mlx_ptr, mlx_display.win_ptr, mlx_display.img.img_ptr, 0, 0);
	mlx_loop_hook(mlx_display.mlx_ptr, colorul_useless_thing, &mlx_display);
	mlx_hook(mlx_display.win_ptr, MotionNotify, PointerMotionMask, escape, &mlx_display);
	mlx_loop(mlx_display.mlx_ptr);
} 
 */