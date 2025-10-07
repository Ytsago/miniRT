/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 14:29:29 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 19:09:02 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "miniRT.h"
#include "../../inc/errors.h"

#define MAX_ID 100

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

bool	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

static bool	parse_elements(char *line, t_context *scene)
{
	int	error;

	error = false;
	jump_spaces(&line);
	if (*line == '#' || *line == '\n')
		return (true);
	if (parse_general_elements(line, scene))
		return (true);
	error = parse_texture(line, scene);
	if (error == -1)
		return (false);
	else if (error)
		return (true);
	else if (empty_line(line))
		return (true);
	else if (parse_objects(line, scene))
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
		return (parse_light(line + 1, scene));
	return (false);
}

static bool	parse_objects(char *line, t_context *scene)
{
	int	error;

	error = 0;
	if (!ft_strncmp("sp", line, 2) && (line[2] == ' ' || line[2] == '\t'))
		error = add_object(scene, new_sphere(scene, &line));
	else if (!ft_strncmp("pl", line, 2) && (line[2] == ' ' || line[2] == '\t'))
		error = add_object(scene, new_plane(scene, &line));
	else if (!ft_strncmp("cy", line, 2) && (line[2] == ' ' || line[2] == '\t'))
		error = add_object(scene, new_cylinder(scene, &line));
	else if (!ft_strncmp("co", line, 2) && (line[2] == ' ' || line[2] == '\t'))
		error = add_object(scene, new_cone(scene, &line));
	else if (!ft_strncmp("ch", line, 2) && (line[2] == ' ' || line[2] == '\t'))
		error = add_object(scene, new_checkerboard(scene, &line));
	else if (!empty_line(line))
		print(2, "%sline %d starts with an unknown identifier\n",
			X_ERROR, scene->line_number);
	if (!error)
		print(2, "%sline %d Error while parsing an object\n",
			X_ERROR, scene->line_number);
	return (error);
}
