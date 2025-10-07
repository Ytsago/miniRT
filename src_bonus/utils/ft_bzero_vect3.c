/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero_vect3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:10:10 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/26 15:19:49 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vect3.h"
#include <stdint.h>

void	ft_bzero_vect3(t_vect3 *self)

{
	self->coords[0] = 0;
	self->coords[1] = 0;
	self->coords[2] = 0;
}
