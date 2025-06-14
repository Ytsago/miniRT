/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_reporting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:17 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 21:05:42 by yabokhar         ###   ########.fr       */
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
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, path) + 14;
	string_length += ft_strcat(buffer + 14, strerror(errno)) + 1;
	buffer[string_length] = '\n';
	buffer[++string_length] = '\0';
	write(STDERR, buffer, string_length);
	exit(FAILURE);
}

bool	multiple_declarations_error(t_context *scene, const char *element)

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

bool	print_error_then_return_false(const char *error_description)

{
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, error_description) + 14;
	write(STDERR, buffer, string_length);
	return (false);
}
