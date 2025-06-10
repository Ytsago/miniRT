/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_reporting.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:46:17 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/10 17:53:27 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_error_then_exit_failure(char *error_description)

{
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, error_description) + 14;
	write(STDERR_FILENO, buffer, string_length);
	exit(EXIT_FAILURE);
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
	write(STDERR_FILENO, buffer, string_length);
	exit(EXIT_FAILURE);
}

bool	print_error_then_return_false(char *error_description)

{
	char	buffer[128];
	short	string_length;

	ft_strcpy(buffer, "Error\nminiRT: ");
	string_length = ft_strcat(buffer + 14, error_description) + 14;
	write(STDERR_FILENO, buffer, string_length);
	return (false);
}

bool	print_character_error_then_return_false(char c, char *err_description)

{
	char	buffer[128];
	char	buffer_bis[4];
	short	string_length;

	buffer_bis[0] = '`';
	buffer_bis[1] = c;
	buffer_bis[2] = '\'';
	buffer_bis[3] = '\0';
	ft_strcpy(buffer, "Error\nminiRT: ");
	ft_strcat(buffer + 14, buffer_bis);
	string_length = ft_strcat(buffer + 17, err_description) + 17;
	write(STDERR_FILENO, buffer, string_length);
	return (false);
}
