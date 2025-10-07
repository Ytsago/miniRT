/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:35 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 22:43:09 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "errors.h"

#define W 0
#define H 1

void		attribute_threads(t_context *scene, short img_width);

void	attribute_threads(t_context *scene, short img_width)

{
	t_threads	*threads;
	short		base_height;
	short		remainder;
	short		i;

	base_height = scene->img[H];
	remainder = scene->img[H];
	scene->online_processors = 1;
	scene->threads = malloc(sizeof(t_threads) * online_processors);
	if (!scene->threads)
		error_malloc_failure_for_threads_array(scene);
	threads = scene->threads;
	i = -1;
	while (++i < online_processors)
	{
		threads[i].index = i;
		threads[i].scene = scene;
		threads[i].screen_parts[H] = base_height + (i < remainder);
		threads[i].screen_parts[W] = img_width;
		threads[i].elapsed_time = 0;
	}
}
