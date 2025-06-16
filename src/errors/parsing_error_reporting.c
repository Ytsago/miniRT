/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_reporting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:17 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/16 11:42:38 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/errors.h"
#include "miniRT.h"

void	print_error_then_exit_failure(const char *error_description)

{
	print(STDERR, "%s%s", X_ERROR, error_description);
	exit(FAILURE);
}

void	print_error_from_open_function_then_exit_failure(const char *path)

{
	print(STDERR, "%s%s: %s\n", X_ERROR, path, strerror(errno));
	exit(FAILURE);
}

void	multiple_declarations_error(t_context *scene, const char *element)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(STDERR, "%s%s: line %d: *** ", X_ERROR, file_name, line_no);
	print(STDERR, "multiple declarations of general element %s\n", element);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	exit(FAILURE);
}

void	precision_lost_error(t_context *scene, const char *elem, const char *p)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(STDERR, "%s%s: line %d: *** ", X_ERROR, file_name, line_no);
	print(STDERR, "%s %s precision lost (too many digits)\n", elem, p);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	exit(FAILURE);
}

void	range_error(t_context *scene, const char *elem, char *min, char *max)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(STDERR, "%s%s: line %d: *** ", X_ERROR, file_name, line_no);
	print(STDERR, "%s must be in range [%s,%s]\n", elem, min, max);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	exit(FAILURE);
}
