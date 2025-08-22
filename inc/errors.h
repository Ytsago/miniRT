/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:14:22 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 10:44:11 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H
# define FAILURE 1
# define STDERR 2
# define X_ERROR "Error\nminiRT: "
# define NO_SPACE "each parameter must be separated by a space\n"

#include <stddef.h>
#include <sys/types.h>
#include <stdbool.h>
#include <errno.h>
#include "miniRT.h"

short	ft_strcpy(char *dest, const char *src);
short	ft_strcat(char *dest, const char *src);
short	ft_strcmp(const char *s1, const char *s2);
ssize_t write(int fildes, const void *buf, size_t nbyte);
void	exit(int status);
char	*strerror(int errnum);

void	multiple_declarations_error(t_context *scene, const char *element);
void	excessive_params_error(t_context *scene, const char *element, char n);
void	no_space_error(t_context *scene);
void	no_comma_error(t_context *scene);
void	precision_lost_error(t_context *s, const char *elem, const char *p);
void	range_error(t_context *scene, const char *elem, char *min, char *max);
bool	print_error_then_return_false(const char *error_description);
bool	print_space_then_error_then_return_false(const char *element);
void	print_error_then_exit_failure(const char *error_description);
void	print_error_from_open_function_then_exit_failure(const char *path);
int8_t	error_malloc_failure_for_threads_array(t_context *scene);

#endif
