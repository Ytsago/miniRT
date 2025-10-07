/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 19:07:24 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 19:07:52 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	get_path(char **str, char **save_path, t_pict **img)
{
	char	*path;

	jump_spaces(str);
	path = extract_str(*str, " \t\n");
	if (!path)
		return (false);
	(*str) += ft_strlen(path);
	if (!ft_strncmp(path, "NONE", 5))
	{
		*img = NULL;
		free (path);
		return (true);
	}
	*save_path = path;
	return (true);
}

int	parse_texture(char *line, t_context *scene)
{
	t_text		new;

	if (*line != 'T' && (!*(line + 1)) && !is_space(*(line + 1)))
		return (false);
	line++;
	ft_fbzero(&new, sizeof(t_text));
	jump_spaces(&line);
	if (!get_color(scene, &line, &new.based))
		return (false);
	if (!get_path(&line, &new.path[0], &new.img[0]))
		return (false);
	if (!get_path(&line, &new.path[1], &new.img[1]))
		return (false);
	jump_spaces(&line);
	if (*line != '\n' && *line)
		return (false);
	if (vector_push(scene->textures, &new) == -1)
	{
		free(new.path[0]);
		free(new.path[1]);
		vector_destroy(scene->textures);
		return (-1);
	}
	return (true);
}
