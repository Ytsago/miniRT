/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:29:29 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/03 18:23:27 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include <stdio.h>

void		parse_parameters(t_context *scene);
static bool	interpret_and_load_parameters(char *line, t_context *scene);

void	parse_parameters(t_context *scene)

{
	char	*line;

	line = get_next_line(scene->fd);
	if (!line || !line[0])
	{
		write(2, "Error\n", 6);
		write(2, "miniRT: empty .rt file\n", 23);
		close(scene->fd);
		exit(EXIT_FAILURE);
	}
	while (line)
	{
		if (!interpret_and_load_parameters(line, scene))
		{
			close(scene->fd);
			free(line);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(scene->fd);
	}
	close(scene->fd);
}

static bool	interpret_and_load_parameters(char *line, t_context *scene)

{
	if (line[0] == 'A')
		if (!parse_ambient_lightning(line + 1, scene))
			return (false);
	return (true);
}
