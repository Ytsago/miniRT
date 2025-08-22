/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_error_reporting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:33:59 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 12:29:31 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_int.h"
#include "mlx_struct.h"

void	mlx_destroy(t_mlx *display)

{
	mlx_loop_end(display->mlx_ptr);
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	mlx_destroy_image(display->mlx_ptr, display->img.img_ptr);
	mlx_destroy_display(display->mlx_ptr);
	free(display->mlx_ptr);
}

int	destroy_display(t_context *scene)

{
	mlx_destroy(&scene->screen_ptr);
	ft_lstclear(&scene->objects, free);
	ft_lstclear(&scene->lights_list, free);
	free(scene->threads);
	exit(1);
}

void	error_failure_from_mlx_new_image(t_context *scene, t_mlx *display)

{
	mlx_destroy_window(display->mlx_ptr, display->win_ptr);
	mlx_destroy_display(display->mlx_ptr);
	free(display->mlx_ptr);
	ft_lstclear(&scene->objects, free);
	ft_lstclear(&scene->lights_list, free);
	free(scene->threads);
	exit(1);
}
