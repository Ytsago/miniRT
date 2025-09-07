/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 11:05:42 by secros            #+#    #+#             */
/*   Updated: 2025/09/04 15:33:43 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "libft.h"

typedef struct s_vector	t_vector;

struct s_vector
{
	void		*tab;
	size_t		element_size;
	size_t		size;
	size_t		capacity;
};

t_vector	*init_vector(size_t element_size);
void		vector_destroy(t_vector	*v);

int			vector_push(t_vector *v, void *element);
int			vector_pop(t_vector *v);
int			vector_get(t_vector *v, size_t index, void *out);
int			vector_set(t_vector *v, size_t index, void *in);

size_t		vector_size(t_vector *v);
size_t		vector_capacity(t_vector *v);
int			vector_resize(t_vector *v, size_t new_size);

#endif
