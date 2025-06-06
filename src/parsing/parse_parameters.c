/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:29:29 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/06 11:14:51 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"

void		parse_parameters(t_context *scene);
static bool	interpret_and_load_parameters(char *line, t_context *scene);
static bool	parse_general_parameters(char *line, t_context *scene);

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
	while (*line)
	{
		if (*line == ' ')
			while (*line == ' ')
				++line;
		else if (*line == 'A' || *line == 'C' || *line == 'L')
			if (!parse_general_parameters(line, scene))
				return (false);
		++line;
	}
	return (true);
}

static bool	parse_general_parameters(char *line, t_context *scene)

{
	const char	identifier = *line;

	if (identifier == 'A')
	{
		if (!parse_ambient_lightning(line + 1, scene))
			return (false);
	}
	else if (identifier == 'C')
		return (true);
	else if (identifier == 'L')
		return (true);
	return (false);
}
