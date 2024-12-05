/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:46:50 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/03 19:41:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	sphere_intersect(t_vector cam_center, t_vector ray, t_figure *obj)
{
	//<D,D>x^2 + (2<OC,D>)x + <OC,OC> - r^2 = 0
	//O is camera center
	//C is spher center
	//D is a ray direction
 	t_vector	cam_sphere_vec;//cam_to_sphere(OC)
	t_math		math;

	obj->point.dist = 0;
	math.a = vec_dot_product(ray, ray);/////ray=ray_direction (D)
	cam_sphere_vec = vec_subtract(cam_center, obj->sphere->center);
	math.b = 2.0 * vec_dot_product(cam_sphere_vec, ray);
	math.c = vec_dot_product(cam_sphere_vec, cam_sphere_vec) - obj->sphere->radius * obj->sphere->radius;
	math.disc = math.b * math.b - 4 * math.c * math.a;
	if (math.disc < 0)
		return (0);
	// else
	// 	return ((-(math.b) - sqrt(math.disc)) / (2.0 * math.a));
	math.x1 = ((-math.b) - sqrt(math.disc)) / (2 * math.a);
	math.x2 = ((-math.b) + sqrt(math.disc)) / (2 * math.a);
	// + sqrt-oby chem hashve vortev mez motik tochkena petq,vata?
	// if (math.x1 > 0 && math.x2 > 0)
	// {
	// 	if (math.x1 > math.x2)
	// 		obj->point.dist = math.x2;
	// 	else
	// 		obj->point.dist = math.x1;
	// }
	// else if (math.x1 > 0)
	// 	obj->point.dist = math.x1;
	// else if (math.x2 > 0)
	// 	obj->point.dist = math.x2;
	find_hit_distance(&obj, math);
	return (obj->point.dist);




	
}

void	find_hit_distance(t_figure **obj, t_math dot)
{
	// (*obj)->point.is_inside = 1;
	if (dot.x1 > __FLT_EPSILON__ || dot.x2 > __FLT_EPSILON__)
	{
		if (dot.x1 > __FLT_EPSILON__ && dot.x2 > __FLT_EPSILON__)
		{
			(*obj)->point.dist = fmin(dot.x1, dot.x2);
			// (*obj)->point.is_inside = 0;
		}
		else if (dot.x1 > __FLT_EPSILON__)
			(*obj)->point.dist = dot.x1;
		else
			(*obj)->point.dist = dot.x2;
	}
}
