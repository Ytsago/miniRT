/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/07 16:58:03 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/07 18:20:07 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

short	ft_strcat(char *dest, const char *src)

{
	short	i;
	short	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (i + j);
}
