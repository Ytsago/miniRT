/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:38:37 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/20 21:10:10 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "vect3.h"
#include "../../inc/errors.h"
#define PARS_CAMERA_ERR "camera parsing error after setting horizontal fov\n"

bool		parse_camera(char *line, t_context *scene);
static void	get_view_point(t_context *scene, char **line, double p[3], short i);
static bool	get_nov(t_context *scene, char **line, t_vect3 *result);
static void	get_horizontal_fov(t_context *s, char **line, short *horizon_fov);

bool	parse_camera(char *line, t_context *scene)

{
	t_camera	*parameters;

	if (scene->element_has_been_declared[CAMERA])
		multiple_declarations_error(scene, "camera");
	jump_spaces(&line);
	parameters = &scene->camera;
	get_view_point(scene, &line, parameters->view_point.coords, 0);
	if (!get_nov(scene, &line, &parameters->orientation_vector))
		return (false);
	jump_spaces(&line);
	get_horizontal_fov(scene, &line, &parameters->horizontal_fov);
	jump_spaces(&line);
	if (*line != '\0' && *line != '\n' && *line != ' ')
		excessive_params_error(scene, "camera", '3');
	return (true);
}

static void	get_view_point(t_context *scene, char **line, double p[3], short i)

{
	char	*end;

	p[i] = ft_strtod(*line, &end, NULL);
	*line = end;
	if (i < 2 && **line != ',')
		no_comma_error(scene);
	else if (**line == ',')
		++(*line);
	if (i < 2)
		get_view_point(scene, line, p, ++i);
	if (i == 2 && **line != ' ')
		no_space_error(scene);
}

static bool	get_nov(t_context *scene, char **line, t_vect3 *result)

{
	if (**line == ' ')
		(*line)++;
	if (!get_vect3_value(scene, line, result))
		return (false);
	if (result->coords[X] < -1.0 || result->coords[X] > 1.0)
		range_error(scene, "camera 3d normalized orientation vec", "-1", "1");
	if (result->coords[Y] < -1.0 || result->coords[Y] > 1.0)
		range_error(scene, "camera 3d normalized orientation vec", "-1", "1");
	if (result->coords[Z] < -1.0 || result->coords[Z] > 1.0)
		range_error(scene, "camera 3d normalized orientation vec", "-1", "1");
	if (**line != ' ')
		no_space_error(scene);
	return (true);
}

static void	get_horizontal_fov(t_context *s, char **line, short *horizon_fov)

{
	if (**line == '-')
		range_error(s, "camera horizontal fov", "0", " ...");
	*horizon_fov = 0;
	if (**line < '0' && **line > '9')
		range_error(s, "camera horizontal fov", "0", "180");
	while (**line >= '0' && **line <= '9')
	{
		*horizon_fov = *horizon_fov * 10 + **line - '0';
		++(*line);
	}
	if (**line != '\0' && **line != '\n' && **line != ' ')
		no_space_error(s);
	if (*horizon_fov < 0 || *horizon_fov > 180)
		range_error(s, "camera horizontal fov", "0", "180");
}
