/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:11:57 by adel              #+#    #+#             */
/*   Updated: 2024/12/09 13:04:05 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	get_sphere_uv(t_sphere *sphere, t_vector point, double *u, double *v)
{
	t_vector	p;
	double		theta;
	double		phi;

	p = vec_subtract(point, sphere->center);
	vec_normalize(&p);

	theta = acos(p.y);
	phi = atan2(p.z, p.x);

	*u = (phi + M_PI) / (2 * M_PI);
	*v = theta / M_PI;
}

t_color	get_xpm_color(t_img *texture, double u, double v)
{
	int		x;
	int		y;
	char	*pixel;
	t_color	color;

	if (!texture || !texture->img_pixels_ptr) {
		color.red = 0;
		color.green = 0;
		color.blue = 0;
		return (color);
	}
	x = (int)(u * texture->width) % texture->width;
	y = (int)(v * texture->height) % texture->height;
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
	{
		color.red = 0;
		color.green = 0;
		color.blue = 0;
		return (color);
	}
	pixel = texture->img_pixels_ptr + (y * texture->line_len + x * (texture->bits_per_pixel / 8));
	color.red = *(unsigned char *)(pixel + 2);
	color.green = *(unsigned char *)(pixel + 1);
	color.blue = *(unsigned char *)(pixel);
	return (color);
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
