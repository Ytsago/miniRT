/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 10:24:14 by secros            #+#    #+#             */
/*   Updated: 2025/09/04 15:30:59 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	*init_vector(size_t element_size)
{
	t_vector	*new;

	new = malloc(sizeof(t_vector));
	if (!new)
		return (NULL);
	new->capacity = 1;
	new->size = 0;
	new->element_size = element_size;
	new->tab = malloc(new->capacity * element_size);
	ft_fbzero(new->tab, new->capacity * element_size);
	if (!new->tab)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

void	vector_destroy(t_vector	*v)
{
	if (!v)
		return ;
	free(v->tab);
	free(v);
	return ;
}
