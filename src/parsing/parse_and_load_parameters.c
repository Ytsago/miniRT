/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_load_parameters.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:29:29 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 19:19:13 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"

void		parse_and_load_parameters(t_context *scene);
static bool	interpret_and_load_parameters(char *line, t_context *scene);
static bool	parse_general_parameters(char *line, t_context *scene);

void	parse_and_load_parameters(t_context *scene)

{
	char	*line;

	line = get_next_line(scene->fd);
	if (!line || !line[0])
	{
		close(scene->fd);
		print_error_then_exit_failure("empty .rt file\n");
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
		scene->element_has_been_declared[AMBIENT_LIGHTNING] = true;
	}
	else if (identifier == 'C')
		return (true);
	else if (identifier == 'L')
		return (true);
	return (true);
}
