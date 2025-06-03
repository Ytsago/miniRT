/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:54:55 by secros            #+#    #+#             */
/*   Updated: 2025/06/03 18:23:54 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdbool.h>

# define AMBIENT_LIGHTNING 0
# define CAMERA 1
# define LIGHT 2
# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct s_ambient_lightning
{
	float			ratio;
	unsigned short	colors[3];
}	t_ambient_lightning;

typedef struct s_context
{
	int					fd;
	bool				element_has_been_declared[3];
	t_ambient_lightning	ambient_lightning;
}	t_context;

int		main(int argc, const char *argv[]);

void	initialize_scene_variables(t_context *scene);
void	parse_arguments(int argc, const char *argv[], int *fd);
void	parse_parameters(t_context *scene);
bool    parse_ambient_lightning(char *line, t_context *scene);

#endif
