/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 19:40:50 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/05 16:56:40 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ray_tracing(t_scene *scene)
{
	double		ray_x;
	double		ray_y;
	scene->vplane = get_view_plane(scene);
	scene->vplane->y_angle = scene->height / 2;
	while (scene->vplane->y_angle >= (scene->height / 2) * (-1))
	{
		scene->vplane->mlx_x = 0;\
		ray_y = scene->vplane->pixel_y * scene->vplane->y_angle;
		scene->vplane->x_angle = (scene->width / 2) * (-1);
		while (scene->vplane->x_angle <= scene->width / 2)
		{
			ray_x = scene->vplane->pixel_x * scene->vplane->x_angle;
			scene->ray = look_at(scene, ray_x, ray_y);
			my_mlx_pixel_put(scene->img, scene->vplane->mlx_x, scene->vplane->mlx_y, color_in_current_pixel(scene));
			scene->vplane->mlx_x++;
			scene->vplane->x_angle++;
		}
		scene->vplane->mlx_y++;
		scene->vplane->y_angle--;
	}
}

void	get_pixel_color(int *color, t_figure *obj, t_scene *scene)
{
	t_color specular;
	t_color	light_in_vec;

	if (!obj)
		return ;
	obj->point.inter_pos = sum_vect(scene->camera->center, num_product_vect(scene->ray,
		obj->point.dist));
	set_inter_normal_vec(scene, obj);
	*color = rgb_color_to_hex(obj->color);
	specular = new_color(0, 0, 0);
	light_in_vec = compute_light(scene, obj, &specular);
	*color = rgb_color_to_hex(add_rgb_light(multiply_rgbs(light_in_vec, \
		(obj->color)), specular));
}

int	color_in_current_pixel(t_scene *scene)
{
	int			color;
	t_figure	*obj;
	double		closest_dot;

	closest_dot = INFINITY;
	obj = NULL;
	closest_dot = closest_inter(scene->camera->center, scene->ray, scene->figure, &obj);
	if (closest_dot == INFINITY)
		color = 0;
	else
		get_pixel_color(&color, obj, scene);
	return (color);
}

double	closest_inter(t_vector pos, t_vector ray, t_figure *figure, t_figure **obj)
{
	double		dot;
	double		closest_dot;

	dot = INFINITY;
	closest_dot = INFINITY;
	while (figure)
	{
		if (figure->type == SPHERE)
			dot = sphere_intersect(pos, ray, figure);
		else if (figure->type == PLANE)
			dot = plane_inter(pos, ray, figure);
		else if (figure->type == CYLINDER)
			dot = cylinder_intersection(pos, ray, figure);
		if (dot > __FLT_EPSILON__ && dot < closest_dot)
		{
			closest_dot = dot;
			*obj = figure;
		}
		figure = figure->next;
	}
	return (closest_dot);
}

double	closest_inter_dlya_shadow(t_vector pos, t_vector ray, t_figure *figure)
{
	double		dot;

	dot = INFINITY;
	if (figure->type == SPHERE)
		dot = sphere_intersect(pos, ray, figure);
	else if (figure->type == PLANE)
		dot = plane_inter(pos, ray, figure);
	else if (figure->type == CYLINDER)
		dot = cylinder_intersection(pos, ray, figure);
	return (dot);
}
