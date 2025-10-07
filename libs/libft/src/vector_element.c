/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_element.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:04:32 by secros            #+#    #+#             */
/*   Updated: 2025/10/07 21:11:51 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int	vector_push(t_vector *v, void *element)
{
	if (!v || !element)
		return (-1);
	if (v->size >= v->capacity)
	{
		if (vector_resize(v, v->capacity * 2 * v->element_size) == -1)
			return (-1);
	}
	ft_memcpy((char *)v->tab + v->size * v->element_size, \
element, v->element_size);
	v->size++;
	return (0);
}

int	vector_pop(t_vector *v)
{
	if (!v || v->size == 0)
		return (-1);
	v->size--;
	return (0);
}

int	vector_get(t_vector *v, size_t index, void *out)
{
	if (!v || index >= v->size || !out)
		return (-1);
	ft_memcpy((char *)out, v->tab + index * v->element_size, v->element_size);
	return (0);
}

int	vector_set(t_vector *v, size_t index, void *in)
{
	if (!v || index >= v->size || !in)
		return (-1);
	ft_memcpy((char *)v->tab + index * v->element_size, in, v->element_size);
	return (0);
}

void	*vector_get_addr(t_vector *v, size_t index)
{
	if (index > v->size)
		return (NULL);
	return (&v->tab[v->element_size * index]);
}
