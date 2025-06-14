/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:38:37 by yabokhar          #+#    #+#             */
/*   Updated: 2025/06/14 20:56:46 by yabokhar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "libft.h"
#include "../../inc/errors.h"
#define VIEW_POINT_ERROR "orientation vector coords must be in range[-1,1]\n"
#define COMMA_ERROR "camera view points values must be separated by a comma\n"
#define NEG_HORIZONTAL_FOV_ERR "camera horziontal fov must be positive\n"
#define HORIZON_FOV_RANGE_ERR "camera horizontal fov must be in range [0,180]\n"
#define PARS_CAMERA_ERR "camera parsing error after setting horizontal fov\n"
#define CAMERA_PARAMS_NB_ERR "camera parameters has more than three variables\n"

bool		parse_camera(char *line, t_context *scene);
static bool	get_view_point(char **line, float view_point[3], short index);
static bool	get_nov(char **line, t_vect3 *result);
static bool	get_horizontal_fov(char **line, short *horizontal_fov);

bool	parse_camera(char *line, t_context *scene)

{
	t_camera	*parameters;

	if (scene->element_has_been_declared[LIGHT])
		multiple_declarations_error(scene, "light");
	jump_spaces(&line);
	parameters = &scene->camera;
	if (!get_view_point(&line, parameters->view_point, 0))
		return (false);
	if (!get_nov(&line, &parameters->orientation_vector))
		return (false);
	jump_spaces(&line);
	if (!get_horizontal_fov(&line, &parameters->horizontal_fov))
		return (false);
	jump_spaces(&line);
	if (*line != '\0' && *line != '\n' && *line != ' ')
		return (print_error_then_return_false(CAMERA_PARAMS_NB_ERR));
	return (true);
}

static bool	get_view_point(char **line, float view_point[3], short index)

{
	char	*end;

	view_point[index] = ft_strtod(*line, &end, NULL);
	*line = end;
	if (index < 2 && **line != ',')
		return (print_error_then_return_false(COMMA_ERROR));
	else if (**line == ',')
		++(*line);
	if (index < 2)
		return (get_view_point(line, view_point, ++index));
	if (index == 2 && **line != ' ')
		return (print_error_then_return_false(NO_SPACE));
	return (true);
}

static bool	get_nov(char **line, t_vect3 *result)

{
	if (**line == ' ')
		(*line)++;
	if (!get_vect3_value(line, result))
		return (false);
	if (result->x < -1.0 || result->x > 1.0)
		return (print_error_then_return_false(VIEW_POINT_ERROR));
	if (result->y < -1.0 || result->y > 1.0)
		return (print_error_then_return_false(VIEW_POINT_ERROR));
	if (result->z < -1.0 || result->z > 1.0)
		return (print_error_then_return_false(VIEW_POINT_ERROR));
	if (**line != ' ')
		return (print_error_then_return_false(NO_SPACE));
	return (true);
}

static bool	get_horizontal_fov(char **line, short *horizontal_fov)

{
	if (**line == '-')
		return (print_error_then_return_false(NEG_HORIZONTAL_FOV_ERR));
	*horizontal_fov = 0;
	if (**line < '0' && **line > '9')
		return (print_error_then_return_false(HORIZON_FOV_RANGE_ERR));
	while (**line >= '0' && **line <= '9')
	{
		*horizontal_fov = *horizontal_fov * 10 + **line - '0';
		++(*line);
	}
	if (**line != '\0' && **line != '\n' && **line != ' ')
		return (print_error_then_return_false(PARS_CAMERA_ERR));
	if (*horizontal_fov < 0 || *horizontal_fov > 180)
		return (print_error_then_return_false(HORIZON_FOV_RANGE_ERR));
	return (true);
}
