/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 13:33:49 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/03 14:24:37 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdbool.h>

void		parse_arguments(int argc, const char *argv[]);
static bool	first_argument_is_not_rt(const char *first_argument);
static void	print_error_then_exit_failure(const char *error);

void	parse_arguments(int argc, const char *argv[])

{
	if (argc < 2)
		print_error_then_exit_failure("miniRT: no argument provided\n");
	if (first_argument_is_not_rt(argv[1]))
		print_error_then_exit_failure("miniRT: invalid file\n");
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

static void	print_error_then_exit_failure(const char *error)

{
	write(2, "Error\n", 6);
	write(2, error, ft_strlen(error));
	exit(EXIT_FAILURE);
}
