/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:54:55 by secros            #+#    #+#             */
/*   Updated: 2025/06/12 12:53:35 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "vect3.h"
# include "mlx_struct.h"
# include "libft.h"

# define AMBIENT_LIGHTNING 0
# define CAMERA 1
# define LIGHT 2
# define X 0
# define Y 1
# define Z 2
# define RED 0
# define GREEN 1
# define BLUE 2

typedef struct s_object		t_object;

enum e_obj
{
	SPHERE,
	CYLINDER,
	PLANE,
};


typedef struct s_ambient_lightning
{
	float			ratio;
	t_color			color;
}	t_ambient_lightning;

typedef struct	s_camera
{
	float	view_point[3];
	t_vect3	orientation_vector;
	short	horizontal_fov;
}	t_camera;

typedef struct s_light
{
	t_point3	light_point;
	double		brightness_ratio;
	t_color		color;
}	t_light;

typedef struct s_context
{
	int					fd;
	bool				element_has_been_declared[3];
	short				number_of_objects;
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
	t_list				*obj;
}	t_context;

struct	s_object
{
	enum e_obj	type;
	t_point3	pos;
	t_vect3		orientation;
	t_color		color;
	t_vect3		size;
};


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
bool	print_character_error_then_return_false(char c, char *error_description);
bool	parse_object(char *line, t_context *scene);
bool	get_unique_value(char **line, double *value);
bool	get_vect3_value(char **line, void *element);
bool	get_color(char **line, t_color *color);

#endif
