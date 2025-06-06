/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/06 11:29:39 by secros            #+#    #+#             */
/*   Updated: 2025/06/06 15:00:46 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"

bool	get_pos(char **line, t_object *obj)
{
	int		i;
	double	x[3];
	bool	precision;

	i = 0;
	while (i < 3)
	{
		x[i] = ft_strtod(line, NULL, &precision);
		if (precision)
		{
			ft_putstr_fd("Error\nPrecision lost...\n", 2);
			return (1);
		}
		while (*line && line != ',');
			line++;
	}
}

t_object	*new_object(char *line, enum e_obj type)
{
	t_object	*new;

	new = malloc(sizeof(t_object));
	if (!new)
		return (NULL);
	new->type = type;
	while (*line && !ft_isdigit(*line))
		line++;
	if (get_pos(&line, new))
		return (free(new), NULL);
}

bool	parse_object(char *line, t_context *scene)
{
	if (!ft_strncmp("sp ", line, 3))
		return (add_object());
	if (!ft_strncmp("pl ", line, 3))
		return (add_object());
	if (!ft_strncmp("cy ", line, 3))
		return (add_object());

}