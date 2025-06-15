/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:33:49 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 20:48:15 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"
#define READ_ONLY 0

void		parse_arguments(int argc, const char *argv[], t_context *scene);
static bool	first_argument_is_not_rt(const char *first_argument);
static bool	failed_to_get_valid_fd(const char *path_to_file, t_context *file);
int			open(const char *path, int oflag, ...);
size_t		ft_strlen(const char *s);

void	parse_arguments(int argc, const char *argv[], t_context *file)

{
	if (argc < 2)
		print_error_then_exit_failure("no argument provided\n");
	if (first_argument_is_not_rt(argv[1]))
		print_error_then_exit_failure("invalid file\n");
	if (failed_to_get_valid_fd(argv[1], file))
		print_error_from_open_function_then_exit_failure(argv[1]);
}

static bool	first_argument_is_not_rt(const char *first_argument)

{
	const unsigned short	argument_length = ft_strlen(first_argument);

	if (argument_length < 4)
		return (true);
	if (!ft_strcmp(&first_argument[argument_length - 3], ".rt"))
		return (false);
	return (true);
}

static bool	failed_to_get_valid_fd(const char *path_to_file, t_context *file)

{
	file->fd = open(path_to_file, READ_ONLY);
	if (file->fd < 0)
		return (true);
	file->file_name = (char *)path_to_file;
	return (false);
}
