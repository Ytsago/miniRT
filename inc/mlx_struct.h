/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:07:04 by secros            #+#    #+#             */
/*   Updated: 2025/06/18 19:15:01 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_STRUCT_H
#define MLX_STRUCT_H

# include "mlx.h"

typedef struct s_mlx		t_mlx;
typedef struct s_pict		t_pict;

struct s_pict
{
	void	*img_ptr;
	char	*addr;
	int		l_size;
	int		bbp;
	int		endian;
};

struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_pict	*img;
};

typedef union u_color
{
	unsigned int	color;
	struct
	{
		unsigned char b;
		unsigned char g;
		unsigned char r;
		unsigned char a;
	};
} t_color;

t_mlx	*get_display(int height, int width, char *title);
t_pict	*new_image(t_mlx *display, int width, int height);
int		destroy_display(t_mlx *display);

#endif
