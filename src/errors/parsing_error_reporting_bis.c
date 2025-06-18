/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_reporting_bis.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:17 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/18 14:23:55 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/errors.h"
#include "miniRT.h"

void	excessive_params_error(t_context *scene, const char *element, char n)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(STDERR, "%s%s: line %d: *** %s has more than %d parameters\n" \
		, X_ERROR, file_name, line_no, element, n);
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	exit(FAILURE);
}

void	no_space_error(t_context *scene)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(STDERR, "%s%s: line %d: *** ", X_ERROR, file_name, line_no);
	print(STDERR, "parameters must be separated by a space\n");
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	exit(FAILURE);
}

void	no_comma_error(t_context *scene)

{
	const char			*file_name = scene->file_name;
	const unsigned int	line_no = scene->line_number;

	print(STDERR, "%s%s: line %d: *** ", X_ERROR, file_name, line_no);
	print(STDERR, "parameters values must be separated by a comma\n");
	close(scene->fd);
	free(scene->line);
	ft_lstclear(&scene->objects, free);
	exit(FAILURE);
}
