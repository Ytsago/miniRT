/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:01:35 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/21 17:06:03 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "errors.h"

void	get_(long *online_processors)

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

bool	attribute_threads(t_context *scene)

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
		return (false);
	threads = scene->threads;
	i = 0;
	while (i < online_processors)
	{
		threads[i].index = i;
		threads[i].scene = scene;
		threads[i].screen_parts[H] = base_height + (i < remainder);
		threads[i].screen_parts[W] = scene->img[W];
		i++;
	}
	return (true);
}
