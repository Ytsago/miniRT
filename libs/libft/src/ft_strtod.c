/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secros <secros@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:05:37 by secros            #+#    #+#             */
/*   Updated: 2025/06/06 11:06:01 by secros           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <math.h>
#include <errno.h>

#define INTPART 9007199254740992.0
#define MAX_DEC_DIG 9
#define DOUBLEMAX 1.7e+308
#define MAXDIGIT 17

static int	skip_space_and_get_sign(const char **str)
{
	int	sign;

	sign = 1;
	while ((**str >= 9 && **str <= 13) || **str == 32)
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			sign = -1;
		(*str)++;
	}
	return (sign);
}

static double	get_integer_part(const char **str, char **end, \
	int *digit_count, bool *lost_prec)
{
	double	digit;
	double	result;

	result = 0;
	*lost_prec = 0;
	while (**str >= '0' && **str <= '9')
	{
		digit = **str - '0';
		(*digit_count)++;
		if (result > (DOUBLEMAX - digit) / 10.0)
		{
			if (end)
				*end = (char *)*str;
			errno = ERANGE;
			return (HUGE_VAL);
		}
		result = result * 10.0 + digit;
		if (result > INTPART)
			*lost_prec = true;
		(*str)++;
	}
	if (end)
		*end = (char *)(*str);
	return (result);
}

static double	get_fractional_part(const char **str, char **end, \
	int *digit_count, bool *lost_prec)
{
	int		divisor;
	double	digit;
	double	result;
	int		local_digit_count;

	divisor = 1.0;
	result = 0.0;
	local_digit_count = 0;
	while (**str >= '0' && **str <= '9')
	{
		digit = **str - '0';
		divisor *= 10;
		result += digit / divisor;
		local_digit_count++;
		(*str)++;
	}
	if (end)
		*end = (char *)(*str);
	if (local_digit_count >= MAX_DEC_DIG)
		*lost_prec = true;
	(*digit_count) += local_digit_count;
	return (result);
}

/**
 * @brief Converts a string to a double precision floating-point number.
 *
 * This function behaves similarly to the standard `strtod`, with support for
 * 
 * optional end-pointer and precision loss detection. Leading whitespace is
 * 
 * skipped and optional signs are handled. Supports basic decimal parsing.
 *
 * @param str The string to convert.
 * @param end (Optional) If not NULL, set to the character after the last
 * 
 * parsed character. If no valid conversion is performed, it is set to `str`.
 * @param precision_flag (Optional) If not NULL, set to true if the result
 * 
 * may have lost precision due to rounding or overflow.
 *
 * @return The parsed double value. On overflow, returns HUGE_VAL and sets
 * errno to ERANGE.
 */
double	ft_strtod(const char *str, char **end, bool	*precision_flag)
{
	int		sign;
	double	fraction;
	double	integer;
	int		digit_count;
	bool	precision;

	digit_count = 0;
	if (!precision_flag)
		precision_flag = &precision;
	fraction = 0.0;
	if (end)
		*end = (char *)str;
	sign = skip_space_and_get_sign(&str);
	if (*str < '0' || *str > '9')
		return (0);
	integer = get_integer_part(&str, end, &digit_count, precision_flag);
	if (errno == ERANGE)
		return (sign * HUGE_VAL);
	str += (*str == '.');
	fraction = get_fractional_part(&str, end, &digit_count, precision_flag);
	if (digit_count >= MAXDIGIT)
		*precision_flag = true;
	return ((integer + fraction) * sign);
}
