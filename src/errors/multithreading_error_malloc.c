/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading_error_malloc.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 10:37:03 by yabokhar          #+#    #+#             */
/*   Updated: 2025/08/22 10:43:40 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "errors.h"

int8_t	error_malloc_failure_for_threads_array(t_context *scene)

{
	print(2, "Error\nminiRT: malloc: %s\n", strerror(errno)); 
	ft_lstclear(&scene->objects, free);
	return (1);
}
