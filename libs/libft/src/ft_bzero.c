/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:39:38 by secros            #+#    #+#             */
/*   Updated: 2025/07/01 17:50:07 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

# ifndef MIN_BZERO_SIZE
#  define MIN_BZERO_SIZE 16
# endif

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

void	ft_fbzero(void *s, size_t n)
{
	if (n < MIN_BZERO_SIZE)
		return (ft_bzero(s, n));
	while ((uintptr_t)s % sizeof(uint64_t) != 0 && n-- > 0)
	{
		*((uint8_t *)s) = 0;
		s = (uint8_t *)s + 1;
	}
	while (n >= sizeof(uint64_t))
	{
		*((uint64_t *)s) = 0;
		s = (uint8_t *)s + sizeof(uint64_t);
		n -= sizeof(uint64_t);
	}
	if (n >= sizeof(uint32_t))
	{
		*((uint32_t *)s) = 0;
		s = (uint8_t *)s + sizeof(uint32_t);
		n -= sizeof(uint32_t);
	}
	while (n > 0)
	{
		*((uint8_t *)s) = 0;
		s = (uint8_t *)s + 1;
		n--;
	}
}

