/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:02:34 by secros            #+#    #+#             */
/*   Updated: 2025/09/03 11:03:58 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

size_t	vector_size(t_vector *v)
{
	return (v->size);
}

size_t	vector_capacity(t_vector *v)
{
	return (v->capacity);
}

int vector_resize(t_vector *v, size_t new_size)
{
	void	*new;
	new = malloc(sizeof(new_size));
	if (!new)
		return (-1);
	ft_memmove(new, v->tab, v->size * v->element_size);
	free(v->tab);
	v->tab = new;
	v->capacity = new_size;
	return (0);
}
