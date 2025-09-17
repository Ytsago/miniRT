#include "miniRT.h"
#include <math.h>

t_vect3		checkerboard_mapping(t_object *obj, t_point3 p, t_vect3 *normal);
static void	compute_uv_axes(t_vect3 normal, t_vect3 *axis_u, t_vect3 *axis_v);

t_vect3	checkerboard_mapping(t_object *obj, t_point3 p, t_vect3 *normal)
{
    t_plane	*pl;
    t_vect3	axis_u;
    t_vect3	axis_v;
    t_vect3	to_point;
    double	du;
	double	dv;

    pl = (t_plane *)obj;
    compute_uv_axes(*normal, &axis_u, &axis_v);
    to_point = vect3_sub(p, pl->pos);
    du = vect3_scalar(to_point, axis_u) / 1.0;
    dv = vect3_scalar(to_point, axis_v) / 1.0;
    if ((((long)floor(du) + (long)floor(dv)) % 2) == 0)
		return (color_to_vec((t_color){.r = 255, .g = 255, .b = 255, .a = 0}));
	return (color_to_vec((t_color){.r = 0, .g = 0, .b = 0, .a = 0}));
}

static void compute_uv_axes(t_vect3 normal, t_vect3 *axis_u, t_vect3 *axis_v)
{
    t_vect3 tmp;
    t_vect3 v;

    tmp = (t_vect3){{1, 0, 0}};
    if (fabs(vect3_scalar(normal, tmp)) > 0.9)
        tmp = (t_vect3){{0, 1, 0}};
    v = vect3_unit(vect3_cross(normal, tmp));
    *axis_v = v;
    *axis_u = vect3_cross(normal, v);
}
