/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_light2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:25:09 by adel              #+#    #+#             */
/*   Updated: 2024/12/05 15:25:46 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_color	diffuse_light(t_figure *obj, t_light *light_fig)
{
	double		intens;
	double		n_dot_l;
	t_vector	light;

	intens = 0;
	light = vec_subtract(light_fig->coords, obj->point.inter_pos);
	vec_normalize(&light);
	n_dot_l = vec_dot_product(obj->point.inter_normal_vec, light);
	if (n_dot_l > 0)
		intens = light_fig->brightness * n_dot_l;
	return (calc_rgb_light(light_fig->color, intens));
}

t_color	specular_light(t_scene *scene, t_light *light_fig, t_figure *obj)
{
	double		spec;
	t_vector	light;
	t_vector	vec_V;
	t_vector	reflected;

	spec = 0;
	light = vec_subtract(light_fig->coords,  obj->point.inter_pos);
	vec_normalize(&light);
	vec_V = vec_subtract(scene->camera->center,  obj->point.inter_pos);
	vec_normalize(&vec_V);
	reflected = reflect_ray(light, obj->point.inter_normal_vec);
	vec_normalize(&reflected);
	if (vec_dot_product(reflected, vec_V) > 0)
	{
		spec = light_fig->brightness * pow(vec_dot_product(reflected, vec_V), \
			obj->specular);
	}
	return (calc_rgb_light(light_fig->color, spec));
}

t_vector	reflect_ray(t_vector light, t_vector p_normal)
{
	t_vector	reflected;

	reflected = num_product_vect(p_normal, 2 * vec_dot_product(light, p_normal));
	reflected = vec_subtract(reflected, light);
	return (reflected);
}
