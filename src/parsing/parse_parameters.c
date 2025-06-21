/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:29:29 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/21 18:28:26 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include "../../inc/errors.h"

void		parse_and_load_parameters(t_context *scene);
static bool	parse_elements(char *line, t_context *scene);
static bool	parse_general_elements(char *line, t_context *scene);
static bool	parse_objects(char *line, t_context *scene);

void	parse_and_load_parameters(t_context *scene)
{
	char	*line;

	line = get_next_line(scene->fd);
	if (!line || !line[0])
	{
		close(scene->fd);
		print_error_then_exit_failure("empty .rt file\n");
	}
	++scene->line_number;
	while (line)
	{
		scene->line = line;
		if (!parse_elements(line, scene))
		{
			close(scene->fd);
			free(line);
			ft_lstclear(&scene->objects, free);
			exit(EXIT_FAILURE);
		}
		free(line);
		line = get_next_line(scene->fd);
		++scene->line_number;
	}
	close(scene->fd);
}

static bool	parse_elements(char *line, t_context *scene)

{
	jump_spaces(&line);
	if (parse_general_elements(line, scene))
		return (true);
	else if (parse_objects(line, scene))
		return (true);
	else if (empty_line(line))
		return (true);
	return (false);
}

static bool	parse_general_elements(char *line, t_context *scene)

{
	if (*line == 'A')
	{
		if (parse_ambient_lightning(line + 1, scene))
			scene->element_has_been_declared[AMBIENT_LIGHTNING] = true;
		return (scene->element_has_been_declared[AMBIENT_LIGHTNING]);
	}
	else if (*line == 'C')
	{
		if (parse_camera(line + 1, scene))
			scene->element_has_been_declared[CAMERA] = true;
		return (scene->element_has_been_declared[CAMERA]);
	}
	else if (*line == 'L')
	{
		if (parse_light(line + 1, scene))
			scene->element_has_been_declared[LIGHT] = true;
		return (scene->element_has_been_declared[LIGHT]);
	}
	return (false);
}

static bool	parse_objects(char *line, t_context *scene)

{
	if (!ft_strncmp("sp ", line, 3))
		return (add_object(scene, new_object(scene, &line, SPHERE)));
	if (!ft_strncmp("pl ", line, 3))
		return (add_object(scene, new_object(scene, &line, PLANE)));
	if (!ft_strncmp("cy ", line, 3))
		return (add_object(scene, new_object(scene, &line, CYLINDER)));
	else if (!empty_line(line))
	{
		print(STDERR, "%sline %d ", X_ERROR, scene->line_number);
		print(STDERR, "starts with an unknown identifier\n");
	}
	return (false);
}
