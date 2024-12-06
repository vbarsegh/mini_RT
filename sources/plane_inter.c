/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:09:09 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/06 22:58:09 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

double	plane_inter(t_vector pos, t_vector ray, t_figure *obj)
{
	double		norm_dot_dir;
	t_vector	p_in_cam_center;

	obj->point.dist = 0;
	calculate_plane_norm(obj, ray);
	obj->plane->orient = obj->point.inter_normal_vec;
	norm_dot_dir = vec_dot_product(obj->plane->orient, ray);
	if (fabs(norm_dot_dir) < __FLT_EPSILON__)
		return (INFINITY);
	p_in_cam_center = vec_subtract(obj->plane->coords, pos);//// P0 - O
	obj->point.dist = vec_dot_product(p_in_cam_center, obj->plane->orient) / norm_dot_dir;//(N . (P - O) / N . D)
    
    if (obj->point.dist < __FLT_EPSILON__) // Пересечение позади луча
	{
		obj->point.dist = 0;//asuma sra kariqy chka gpt-n
        return (INFINITY);
	}
	return (obj->point.dist);
}
