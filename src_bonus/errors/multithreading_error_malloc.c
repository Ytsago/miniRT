/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_error_malloc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:37:03 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 21:45:20 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	error_malloc_failure_for_threads_array(t_context *scene)

{
	print(2, "Error\nminiRT: malloc: %s\n", strerror(errno));
	ft_lstclear(&scene->objects, free);
	ft_lstclear(&scene->lights_list, free);
	clear_texture(scene->textures, &scene->screen_ptr);
	exit(1);
}
