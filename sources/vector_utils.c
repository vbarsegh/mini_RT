/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:58:41 by adel              #+#    #+#             */
/*   Updated: 2024/12/06 23:02:59 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vector	new_vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = 1;
	return (vec);
}

t_vector	vec_subtract(t_vector vec1, t_vector vec2)
{
	t_vector	result;

	result = new_vector(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
	return (result);
}

double	vec_length(t_vector vec)
{
	double	res;
	
	res = sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
	return (res);
}

void	vec_normalize(t_vector *vec)
{
	double	length;
	
	length = vec_length(*vec);
	vec->x /= length;
	vec->y /= length;
	vec->z /= length;
}


t_vector vector_normalize(t_vector v)
{
	double		magnitude;
	t_vector	zero_vector;
	t_vector	normalized_vector;

	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (magnitude == 0)
	{
		zero_vector.x = 0.0;
		zero_vector.y = 0.0;
		zero_vector.z = 0.0;
		zero_vector.w = 0.0;
		return (zero_vector);
	}

	normalized_vector.x = v.x / magnitude;
	normalized_vector.y = v.y / magnitude;
	normalized_vector.z = v.z / magnitude;
	normalized_vector.w = 0.0;

	return normalized_vector;
}


t_vector vec_scale(t_vector v, double scalar)
{
	t_vector	result;
	
	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}