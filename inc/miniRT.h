/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:54:55 by secros            #+#    #+#             */
/*   Updated: 2025/06/07 20:59:58 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdbool.h>

# define AMBIENT_LIGHTNING 0
# define CAMERA 1
# define LIGHT 2
# define X 0
# define Y 1
# define Z 2
# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct s_ambient_lightning
{
	float			ratio;
	short			colors[3];
}	t_ambient_lightning;

typedef struct	s_camera
{
	float	view_point[3];
	short	horizontal_fov;
}	t_camera;

typedef struct s_light
{
	float	light_point[3];
	float	brightness_ratio;
}	t_light;

typedef struct s_context
{
	int					fd;
	bool				element_has_been_declared[3];
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
}	t_context;

int		main(int argc, const char *argv[]);

void	initialize_scene_variables(t_context *scene);
void	parse_arguments_then_get_fd(int argc, const char *argv[], int *fd);
void	parse_and_load_parameters(t_context *scene);
bool    parse_ambient_lightning(char *line, t_context *scene);
bool	parse_camera(char *line, t_context *scene);
bool	parse_light(char *line, t_context *scene);

bool	fill_pallet(short pallet[3], const char *line);
short	ascii_to_rgb(const char **str);

void	jump_spaces(char **str);
void	jump_zeros(char **str);

void	print_error_then_exit_failure(char *error_description);
void	print_error_from_open_function_then_exit_failure(const char *path);
bool	print_error_then_return_false(char *error_description);

#endif
