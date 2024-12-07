/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:11:57 by adel              #+#    #+#             */
/*   Updated: 2024/12/07 20:42:32 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_texture(char *xpm, t_sphere *sphere)
{
	char	**line;
	
	line = split_char(xpm, ':');
	if (!(ft_strcmp(line[0], "txm")))
	{
		sphere->has_texture = true;
		sphere->path = line[1];
		printf("da\n");
		return (0);
	}
	else
		return (1);
}

void	get_texture(t_scene *scene)
{
	t_figure *tmp = scene->figure;
	while (tmp)
	{
		if (tmp->sphere->has_texture == true)
		{
			tmp->sphere->texture.img_ptr = mlx_xpm_file_to_image(scene->mlx->mlx,
				tmp->sphere->path, &tmp->sphere->texture.width, &tmp->sphere->texture.height);
			if (!tmp->sphere->texture.img_ptr)
				err("no xpm\n");
			tmp->sphere->texture.img_pixels_ptr = mlx_get_data_addr(tmp->sphere->texture.img_ptr,
					&tmp->sphere->texture.bits_per_pixel, &tmp->sphere->texture.line_len,
					&tmp->sphere->texture.endian);
			printf("%s\n",tmp->sphere->path);
		}
		tmp = tmp->next;
	}
	
}
void get_sphere_uv(t_sphere *sphere, t_vector point, double *u, double *v)
{
	t_vector	p;
	double		theta;
	double		phi;

	p = vec_subtract(point, sphere->center);
	p = vector_normalize(p);

	theta = acos(p.y);
	phi = atan2(p.z, p.x);

	*u = (phi + M_PI) / (2 * M_PI);
	*v = theta / M_PI;
}

int	get_texture_color(t_img *texture, double u, double v)
{
	int		x;
	int		y;
	char	*pixel;

	x = (int)(u * texture->width) % texture->width;
	y = (int)(v * texture->height) % texture->height;
	pixel = texture->img_pixels_ptr + (y * texture->line_len + x * (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

int	olor_in_current_pixel2(t_scene *scene)
{
	t_figure *current_figure = scene->figure;
	double closest_dist = INFINITY;
	t_figure *closest_figure = NULL;
	t_vector intersection_point;

	while (current_figure)
	{
		double dist = 0;
		if (current_figure->type == SPHERE)
			dist = sphere_intersect(scene->camera->center, scene->ray, current_figure);
		if (dist > 0 && dist < closest_dist)
		{
			closest_dist = dist;
			closest_figure = current_figure;
			intersection_point = sum_vect(scene->camera->center, vec_scale(scene->ray, dist));
		}
		current_figure = current_figure->next;
	}
	if (!closest_figure)
		return (scene->ambient->count);
	if (closest_figure->type == SPHERE && closest_figure->sphere->has_texture)
	{
		double u, v;
		get_sphere_uv(closest_figure->sphere, intersection_point, &u, &v);
		int texture_x = (int)(u * closest_figure->sphere->texture.width);
		int texture_y = (int)(v * closest_figure->sphere->texture.height);
		texture_x %= closest_figure->sphere->texture.width;
		texture_y %= closest_figure->sphere->texture.height;
		char *pixel = closest_figure->sphere->texture.img_pixels_ptr
					  + (texture_y * closest_figure->sphere->texture.line_len)
					  + (texture_x * (closest_figure->sphere->texture.bits_per_pixel / 8));
		return (*(int *)pixel);
	}
	t_color shaded_color = default_shading(scene, closest_figure);
	return (create_int_from_color(shaded_color));
}

t_color	default_shading(t_scene *scene, t_figure *figure)
{
	t_color	object_color;
	t_color	shaded_color;
	double	intensity;
	
	intensity = scene->ambient->intensity;
	object_color = figure->color;
	shaded_color = create_color(
		object_color.red * intensity,
		object_color.green * intensity,
		object_color.blue * intensity
	);

	return (shaded_color);
}

int	create_int_from_color(t_color color)
{
	return ((color.red << 16) | (color.green << 8) | color.blue);
}

t_color	create_color(double r, double g, double b)
{
	t_color	color;

	color.red = r;
	color.green = g;
	color.blue = b;
	return (color);
}
