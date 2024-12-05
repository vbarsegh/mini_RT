/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:56:26 by adel              #+#    #+#             */
/*   Updated: 2024/12/05 16:58:23 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_vplane	*get_view_plane(t_scene *scene)
{
	t_vplane	*vplane;
	double		aspect_ratio;

	vplane = malloc(sizeof(t_vplane));
	if (!vplane)
		exit (1);
	aspect_ratio = WIDTH / scene->height;
	vplane->mlx_x = 0;
	vplane->mlx_y = 0;
	vplane->width = 2 * tan(scene->camera->fov / 2 * (M_PI / 180));
	vplane->height = vplane->width / aspect_ratio;
	vplane->pixel_x = vplane->width / WIDTH;
	vplane->pixel_y = vplane->height / scene->height;
	return (vplane);
}

t_vector	 look_at(t_scene	*scene, double ray_x, double ray_y)
{
	t_vector	up;
	t_vector	new;
	t_vector	right;
	t_vector	ray_dir;

	up = new_vector(0, 1, 0);
	if (fabs(vec_dot_product(scene->camera->direction, up)) > 0.999)
		up = new_vector(0, 0, 1);
	right = vec_cross_product(scene->camera->direction, up);\
	vec_normalize(&right);
	new = vec_cross_product(right, scene->camera->direction);
	vec_normalize(&new);
	ray_dir = sum_vect(sum_vect(num_product_vect(right, ray_x), \
		num_product_vect(new, ray_y)), scene->camera->direction);
	vec_normalize(&ray_dir);
	return (ray_dir);
}
