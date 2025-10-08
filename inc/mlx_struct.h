/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:07:04 by secros            #+#    #+#             */
/*   Updated: 2025/10/08 17:51:04 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

# include <stdbool.h>
# include <stdint.h>
# include "mlx.h"

# define ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_T 116
# define KEY_B 98
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define MOUSE_SENSITIVITY 0.001

typedef struct s_mlx		t_mlx;
typedef struct s_pict		t_pict;
typedef struct s_context	t_context;

struct s_pict
{
	void	*img_ptr;
	char	*addr;
	int		l_size;
	int		bbp;
	int		endian;
	int		size[2];
	char	*path;
};

struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_pict	img;
};

typedef union u_color
{
	uint32_t	color;
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	a;
	};
}	t_color;

void	get_display_and_new_image(t_context *scene, short img[2]);
int		destroy_display(t_context *scene);
void	mlx_destroy(t_mlx *display);
void	destroy_img(t_pict *img, t_mlx *display);
int		handle_key(int keycode, void *params);
int		handle_mouse(int x, int y, void *params);
t_pict	*load_image(t_mlx *display, char *addr);
t_color	coord_to_img(t_pict	*map, double u, double v);

#endif
