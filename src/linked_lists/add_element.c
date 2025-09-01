/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 17:32:23 by yabokhar          #+#    #+#             */
/*   Updated: 2025/09/01 16:52:48 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

bool	add_element(t_context *scene, void *type)

{
	t_list	*new_element;

	if (!type)
		return (false);
	new_element = ft_lstnew(type);
	if (!new_element)
	{
		free(type);
		return (false);
	}
	ft_lstadd_back(&scene->lights_list, new_element);
	return (true);
}
