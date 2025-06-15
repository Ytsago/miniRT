/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_characters.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabokhar <yabokhar@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:38:32 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 15:41:31 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

int	ft_isdigit(int c);
int	ft_issign(int c);

void	jump_spaces(char **str)

{
	while (**str == ' ')
		++(*str);
}

bool	empty_line(char *line)

{
	while ((*line >= '\t' && *line <= '\r') || *line == ' ')
		++line;
	return (*line == '\0' || *line == '\n');
}

bool	verify_and_skip_comma(char **line)

{
	if (**line == ',' && (ft_isdigit(*((*line) + 1))
			|| ft_issign(*((*line) + 1))))
	{
		(*line)++;
		return (false);
	}
	return (true);
}
