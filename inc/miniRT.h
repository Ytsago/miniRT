/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:54:55 by secros            #+#    #+#             */
/*   Updated: 2025/06/19 17:12:49 by secros           ###   ########.fr       */
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

typedef struct s_camera
{
	float	view_point[3];
	t_vect3	prout;
	t_vect3	orientation_vector;
	short	horizontal_fov;
	double	viewport[2];
	t_vect3	focal;
	t_vect3	viewport_u;
	t_vect3	viewport_v;
	t_vect3	pixel_delta_u;
	t_vect3	pixel_delta_v;
	t_vect3	viewport_upper_left;
	t_vect3	pixel_zero;
}	t_camera;

typedef struct s_light
{
	t_point3	light_point;
	double		brightness_ratio;
	t_color		color;
}	t_light;

typedef struct s_context
{
	short				img[2];
	t_ambient_lightning	ambient_lightning;
	t_camera			camera;
	t_light				light;
	t_list				*objects;
	int					fd;
	char				*file_name;
	char				*line;
	unsigned int		line_number;
	bool				element_has_been_declared[3];
}	t_context;

struct	s_object
{
	enum e_obj	type;
	t_point3	pos;
	t_vect3		orientation;
	t_color		color;
	t_vect3		size;
};


int			main(int argc, const char *argv[]);

void		parse_arguments(int ac, const char *av[], t_context *s);
void		parse_and_load_parameters(t_context *scene);
bool   		parse_ambient_lightning(char *line, t_context *scene);
bool		parse_camera(char *line, t_context *scene);
bool		parse_light(char *line, t_context *scene);

bool		add_object(t_context *scene, t_object *object); 
t_object	*new_object(t_context *scene, char **line, enum e_obj type);

void		jump_spaces(char **str);
bool		empty_line(char *line);
bool		verify_and_skip_comma(char **line);

bool		get_unique_value(t_context *scene, char **line, double *value);
bool		get_vect3_value(t_context *scene, char **line, void *element);
bool		get_color(t_context *scene, char **line, t_color *color);

void		get_image_dimensions(short image[2]);
void		get_camera(t_camera *params, short img[2]);

#endif
