/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_reporting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:17 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 19:02:23 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_error_then_exit_failure(char *error_description)

{
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, error_description) + 14;
	write(2, buffer, string_length);
	exit(1);
}

void	print_error_from_open_function_then_exit_failure(const char *path)

{
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, path) + 14;
	string_length += ft_strcat(buffer + 14, strerror(errno));
	buffer[string_length] = '\n';
	buffer[++string_length] = '\0';
	write(2, buffer, string_length);
	exit(1);
}

bool	print_error_then_return_false(char *error_description)

{
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, error_description) + 14;
	write(2, buffer, string_length);
	return (false);
}
