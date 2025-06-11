/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_load_parameters.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:29:29 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/11 16:48:33 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include "libft.h"
#include <stdio.h>

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
	scene->number_of_objects = 0;

	while (*line)
	{
		jump_spaces(&line);
		if (*line == 'A' || *line == 'C' || *line == 'L')
		{
			if (!parse_general_parameters(line, scene))
				return (false);
		}
		// else if (ft_strncmp(line, "sp ", 3))
		// {
		// 	++scene->number_of_objects;
		// }
		else if (parse_object(line, scene))
			return (printf("Obj parsing failded\n"), false);
		++line;
	}
	return (true);
}

static bool	parse_general_parameters(char *line, t_context *scene)
{
	const char	identifier = *line;

	if (identifier == 'A')
	{
		if (scene->element_has_been_declared[AMBIENT_LIGHTNING] && !parse_ambient_lightning(line + 1, scene))
			return (false);
		scene->element_has_been_declared[AMBIENT_LIGHTNING] = true;
	}
	else if (identifier == 'C')
	{
		if (!parse_camera(line + 1, scene))
			return (false);
		scene->element_has_been_declared[CAMERA] = true;
	}
	else if (identifier == 'L')
	{
		if (!parse_light(line + 1, scene))
			return (true);
		scene->element_has_been_declared[LIGHT] = true;
	}
	return (true);
}
