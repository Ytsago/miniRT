/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 10:54:55 by secros            #+#    #+#             */
/*   Updated: 2025/07/04 13:44:07 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdbool.h>
# include "vect3.h"
# include "mlx_struct.h"
# include "libft.h"

typedef struct s_object		t_object;
typedef struct s_viewport	t_viewport;
typedef struct s_sphere		t_sphere;
typedef struct s_cylinder	t_cylinder;
typedef struct s_plane		t_plane;

enum e_obj
{
	SPHERE,
	CYLINDER,
	PLANE,
};

# ifndef e_geo
#  define e_geo
enum e_geo
{
	X,
	Y,
	Z,
};

# endif

enum e_scene
{
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
};

enum e_rgb
{
	RED,
	GREEN,
	BLUE,
};

struct	s_object
{
	enum e_obj	type;
	t_point3	pos;
	t_color		color;
};

struct	s_sphere
{
	enum e_obj	type;
	t_point3	pos;
	t_color		color;
	double		radius;
};

struct	s_cylinder
{
	enum e_obj	type;
	t_point3	pos;
	t_color		color;
	double		radius;
	double		height;
	t_vect3		orientation;
};

struct	s_plane
{
	enum e_obj	type;
	t_point3	pos;
	t_color		color;
	t_vect3		orientation;
};

struct	s_viewport
{
	double	viewport[2];
	t_vect3	viewport_vect[2];
	t_vect3	pixel_deltas[2];
	t_vect3	viewport_upper_left;
	t_vect3	pixel_zero;
};

typedef struct s_ambient_lightning
{
	float			ratio;
	t_color			color;
}	t_ambient_lightning;

typedef struct s_camera
{
	t_vect3		view_point;
	t_vect3		orientation_vector;
	short		horizontal_fov;
	t_vect3		focal;
	t_viewport	viewport;
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
	bool				spectator_mode;
	t_mlx				*screen_ptr;
}	t_context;

int			main(int argc, const char *argv[]);

void		parse_arguments(int ac, const char *av[], t_context *s);
void		parse_and_load_parameters(t_context *scene);
bool   		parse_ambient_lightning(char *line, t_context *scene);
bool		parse_camera(char *line, t_context *scene);
bool		parse_light(char *line, t_context *scene);

bool		add_object(t_context *scene, t_object *object); 
t_object	*new_object(t_context *scene, char **line, enum e_obj type);
t_object	*new_cylinder(t_context *scene, char **line);
t_object	*new_plane(t_context *scene, char **line);
t_object	*new_sphere(t_context *scene, char **line);

void		jump_spaces(char **str);
bool		empty_line(char *line);
bool		verify_and_skip_comma(char **line);

bool		get_unique_value(char **line, double *value);
bool		get_vect3_value(t_context *scene, char **line, void *element);
bool		get_color(t_context *scene, char **line, t_color *color);
void		raytracer(t_context *scene, t_mlx *screen);

void		get_camera(t_camera *params, short img[2]);

t_vect3		color_to_vec(t_color c);
t_color		vec_to_color(t_vect3 v);

void	ft_bzero_vect3(t_vect3 *self);

void	move_camera(t_camera *camera, int keycode);

#endif
