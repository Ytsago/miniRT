/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:07:04 by secros            #+#    #+#             */
/*   Updated: 2025/09/01 17:31:34 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STRUCT_H
# define MLX_STRUCT_H

# include <stdbool.h>
# include <stdint.h>
# include "mlx.h"

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
void	error_failure_from_mlx_new_image(t_context *scene, t_mlx *display);
int		handle_key(int keycode, void *params);
t_pict	*load_image(t_mlx *display, char *addr);

#endif
