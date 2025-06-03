/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:33:49 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/03 15:24:55 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include <string.h>
#include <errno.h>
#include <fcntl.h>

void		parse_arguments(int argc, const char *argv[], int *fd);
static bool	first_argument_is_not_rt(const char *first_argument);
static bool	failed_to_get_valid_fd(const char *path_to_file, int *fd);

void	parse_arguments(int argc, const char *argv[], int *fd)

{
	if (argc < 2)
	{
		write(2, "Error\n", 6);
		write(2, "miniRT: no argument provided\n", 29);
		exit(EXIT_FAILURE);
	}
	if (first_argument_is_not_rt(argv[1]))
	{
		write(2, "Error\n", 6);
		write(2, "miniRT: invalid file\n", 21);
		exit(EXIT_FAILURE);
	}
	if (failed_to_get_valid_fd(argv[1], fd))
	{
		write(2, "Error\nminiRT: open: ", 20);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
		exit(EXIT_FAILURE);
	}
}

static bool	first_argument_is_not_rt(const char *first_argument)

{
	const size_t	argument_length = ft_strlen(first_argument);
	const size_t	index_before_extension = argument_length - 3;

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
