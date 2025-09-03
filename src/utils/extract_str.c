/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 13:19:54 by secros            #+#    #+#             */
/*   Updated: 2025/09/03 13:33:18 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	is_charset(char c, const char *charset)
{
	while (*charset)
	{
		if (c == *charset)
			return (true);
		charset++;
	}
	return (false);
}

static size_t	find_size_until_charset(char *str, const char *charset)
{
	size_t	i;

	i = 0;
	while (str[i] && !is_charset(str[i], charset))
		i++;
	return (i);
}

char	*extract_str(char *str, const char *charset)
{
	return (ft_substr(str, 0, find_size_until_charset(str, charset)));
}
