/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:39:38 by secros            #+#    #+#             */
/*   Updated: 2025/06/26 15:10:55 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = '\0';
		i++;
	}
}

void	ft_bzero_eight_by_eight(void *s, size_t n)
{
	size_t			i;
	const size_t	lim = n / sizeof(uint16_t);

	i = 0;
	while (i < lim)
	{
		((uint16_t *)s)[i] = 0;
		++i;
	}
}
