/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments_then_get_fd.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:33:49 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 19:01:11 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void		parse_arguments_then_get_fd(int argc, const char *argv[], int *fd);
static bool	first_argument_is_not_rt(const char *first_argument);
static bool	failed_to_get_valid_fd(const char *path_to_file, int *fd);

void	parse_arguments_then_get_fd(int argc, const char *argv[], int *fd)

{
	if (argc < 2)
		print_error_then_exit_failure("no argument provided\n");
	if (first_argument_is_not_rt(argv[1]))
		print_error_then_exit_failure("invalid file\n");
	if (failed_to_get_valid_fd(argv[1], fd))
		print_error_from_open_function_then_exit_failure(argv[1]);
}

static bool	first_argument_is_not_rt(const char *first_argument)

{
	const unsigned short	argument_length = ft_strlen(first_argument);
	const short				index_before_extension = argument_length - 3;

	if (argument_length < 4)
		return (true);
	if (!ft_strcmp(&first_argument[index_before_extension], ".rt"))
		return (false);
	return (true);
}

static bool	failed_to_get_valid_fd(const char *path_to_file, int *fd)

{
	*fd = open(path_to_file, O_RDONLY);
	if (*fd < 0)
		return (true);
	return (false);
}
