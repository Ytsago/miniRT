/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect3.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:42:39 by secros            #+#    #+#             */
/*   Updated: 2025/07/03 16:28:30 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECT3_H
# define VECT3_H
# define X 0
# define Y 1
# define Z 2

# include "math.h"
# include <stdbool.h>

/**
 * @brief A 3D object that contain coordinate, x, y, z
 * 
 */
typedef union u_vect3	t_vect3;

/**
 * @brief Similar to t_vect3 but renamed for clarity
 * 
 */
typedef 	t_vect3		t_point3;
union u_vect3
{
	double	coords[3];
	struct
	{
		double x;
		double y;
		double z;
	};
};

/**
 * @brief Add two 3D vector U + V, return the result.
 * 
 * @param first U vector
 * @param second V vector
 * @return t_vect3 struct,
 */
t_vect3	vect3_add(t_vect3 first, t_vect3 second);

/**
 * @brief Substract two 3D vector U - V, return the result.
 * 
 * @param first U vector
 * @param second V vector
 * @return t_vect3 struct,
 */
t_vect3	vect3_sub(t_vect3 first, t_vect3 second);

/**
 * @brief Multiply two 3D vector U * V, return the result.
 * 
 * @param first 
 * @param second 
 * @return t_vect3 
 */
t_vect3	vect3_mult(t_vect3 first, t_vect3 second);

/**
 * @brief Multiply a 3D vector U by t, t is constant, return the result.
 * 
 * @param first U vector
 * @param t A constante
 * @return t_vect3 struct,
 */
t_vect3	vect3_const_mult(t_vect3 first, double t);

/**
 * @brief Divide two 3D vector U / V, return the result.
 * 
 * @param first U Vector
 * @param second V Vector
 * @return t_vect3 struct,
 */
t_vect3	vect3_div(t_vect3 first, t_vect3 second);

/**
 * @brief Divide a 3D vector U / t, t is constant, return the result.
 * 
 * @param first U Vector
 * @param t A constante
 * @return t_vect3 struct,
 */
t_vect3	vect3_const_div(t_vect3 first, double t);

/**
 * @brief Compute the euclidian norm of a 3D vector.
 * 
 * @param vect A 3D vector of type t_vect3
 * @return Euclidian norm (lenght) of the Vector (double)
 */
double	vect3_norm(double v[3]);

/**
 * @brief Compute the scalar product U.V (Dot product) of two 3D Vector.
 * 
 * @param first U Vector
 * @param second V Vector
 * @return The scalar product (double)
 */
double	vect3_scalar(t_vect3 first, t_vect3 second);

/**
 * @brief Compute the Vector product U x V (cross product) of two 3D Vector.
 * 
 * @param first U Vector
 * @param second V Vector
 * @return A new t_vect3 Vector perpendicular to U and V
 */
t_vect3	vect3_cross(t_vect3 first, t_vect3 second);

/**
 * @brief Compute the unit (normalized) Vector of 3D Vector
 * 
 * @param first A 3D vector,
 * @return t_vect3 The normalized 3D Vector,
 */
t_vect3	vect3_unit(t_vect3 first);

/**
 * @brief Negate 3D vector,
 * 
 * @param v -> 3D vector,
 * @return t_vect3 The negated 3D Vector,
 */
t_vect3	vect3_negate(t_vect3 v);

/*t_vect3	color_to_vec(t_color c);

*
 * @brief Convert t_color c into 3D vector,
 * 
 * @param c -> color structure RGB,
 * @return t_vect3 ...,
 */

double			opt_div(double x, double y);
bool			no_fractionnal_part(double x, double y);
unsigned int	power_of_two(int y);


#endif
