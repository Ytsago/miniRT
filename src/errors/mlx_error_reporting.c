/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_error_reporting.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:33:59 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/02 10:52:01 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx_struct.h"

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
