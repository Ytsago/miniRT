/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_reporting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:17 by yabokhar          #+#    #+#             */
/*   Updated: 2025/10/07 21:56:59 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/errors.h"
#include "miniRT.h"

void	print_error_then_exit_failure(const char *error_description)

{
	print(2, "%s%s", X_ERROR, error_description);
	exit(1);
}

void	print_error_from_open_function_then_exit_failure(const char *path)

{
	print(2, "%s%s: %s\n", X_ERROR, path, strerror(errno));
	exit(1);
}

void	multiple_declarations_error(t_context *scene, const char *element)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(2,
		"%s%s: line %d: *** multiple declarations of general element %s\n",
		X_ERROR, file_name, line_no, element);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	clear_texture(scene->textures, &scene->screen_ptr);
	exit(1);
}

void	precision_lost_error(t_context *scene, const char *elem, const char *p)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(2,
		"%s%s: line %d: *** %s %s precision lost (too many digits)\n",
		X_ERROR, file_name, line_no, elem, p);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	clear_texture(scene->textures, &scene->screen_ptr);
	exit(1);
}

void	range_error(t_context *scene, const char *elem, char *min, char *max)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(2,
		"%s%s: line %d: *** %s must be in range [%s,%s]\n",
		X_ERROR, file_name, line_no, elem, min, max);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	clear_texture(scene->textures, &scene->screen_ptr);
	exit(1);
}
