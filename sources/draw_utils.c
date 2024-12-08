/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 01:04:47 by adel              #+#    #+#             */
/*   Updated: 2024/12/09 02:22:34 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	draw(t_scene *scene)
{
	scene->img->img_ptr = mlx_new_image(scene->mlx->mlx, WIDTH, HEIGHT);
	scene->img->img_pixels_ptr = mlx_get_data_addr(scene->img->img_ptr, \
	&scene->img->bits_per_pixel, &scene->img->line_len, &scene->img->endian);
	ray_tracing(scene);
	mlx_put_image_to_window(scene->mlx->mlx,
		scene->mlx->win, scene->img->img_ptr, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	char	*addr_end;

	addr_end = img->img_pixels_ptr + (HEIGHT * img->line_len);
	dst = img->img_pixels_ptr
		+(y * img->line_len + x * (img->bits_per_pixel / 8));
	if (dst >= img->img_pixels_ptr && dst < addr_end)
		*(unsigned int *)dst = color;
}

void	perturb_normal(t_vector *normal, t_vector bump)
{
	*normal = vec_normalize2(sum_vect(*normal, bump));
}

void	get_pixel_color(int *color, t_figure *obj, t_scene *scene)
{
	t_color	specular;
	t_color	light_in_vec;
	t_color texture_color;
	double u, v;

	if (!obj)
		return ;
	texture_color = obj->color;
	obj->point.inter_pos = sum_vect(scene->camera->center, num_product_vect(scene->ray,
		obj->point.dist));
	set_inter_normal_vec(scene, obj);
	if (obj && obj->type == SPHERE && obj->sphere->has_texture == true)
	{
		t_vector intersection_point = sum_vect(scene->camera->center, vec_scale(scene->ray, obj->point.dist));
		get_sphere_uv(obj->sphere, intersection_point, &u, &v);
		if (obj->sphere->has_texture)
			texture_color = get_xpm_color(&obj->sphere->texture, u, v);
		if (obj->sphere->has_bump)
		{
			t_color bump_sample = get_xpm_color(&obj->sphere->bump, u, v);
			t_vector bump_vector = color_to_vector(bump_sample);
			perturb_normal(&obj->point.inter_normal_vec, bump_vector);
		}
	}
	*color = rgb_color_to_hex(obj->color);
	specular = create_color(0, 0, 0);
	light_in_vec = compute_light(scene, obj, &specular);
	*color = rgb_color_to_hex(add_rgb_light(multiply_rgbs(light_in_vec, \
		(texture_color)), specular));
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