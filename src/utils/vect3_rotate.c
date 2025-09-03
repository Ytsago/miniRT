#include "miniRT.h"
#include <math.h>

t_vect3	vect3_rotate(t_vect3 v, t_vect3 axis, double angle)

{
	t_vect3	rot;
	double	c;
	double	s;

	axis = vect3_unit(axis);
	c = cos(angle);
	s = sin(angle);
	rot = vect3_add(
			vect3_const_mult(v, c),
			vect3_add(
				vect3_const_mult(vect3_cross(axis, v), s),
				vect3_const_mult(axis, vect3_scalar(axis, v) * (1 - c))
			)
		);
	return (rot);
}
