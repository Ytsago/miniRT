/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:35 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/02 14:47:31 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "errors.h"

#define W 0
#define H 1

void		attribute_threads(t_context *scene, short img_width);
static void	get_(long *online_processors);

void	attribute_threads(t_context *scene, short img_width)

{
	t_threads	*threads;
	long		online_processors;
	short		base_height;
	short		remainder;
	short		i;

	get_(&online_processors);
	base_height = scene->img[H] / online_processors;
	remainder = scene->img[H] % online_processors;
	scene->online_processors = online_processors;
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

static void	get_(long *online_processors)

{
	*online_processors = sysconf(_SC_NPROCESSORS_ONLN);
	if (*online_processors < 1)
	{
		print(2, "Warning:\nminiRT: shall create an unique thread as \
sysconf(_SC_NPROCESSORS_ONLN) returned %d.\n", (int)*online_processors);
		*online_processors = 1;
	}
	print(1, "miniRT: %d threads available\n", *online_processors);
}
