/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 17:11:57 by adel              #+#    #+#             */
/*   Updated: 2024/12/08 23:23:26 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	init_texture(char *xpm, t_sphere *sphere)
{
	char	**line;

	if (!xpm || !sphere)
		return (1);
	line = split_char(xpm, ':');
	if (!(ft_strcmp(line[0], "txm")))
	{
		sphere->has_texture = true;
		if (open(line[1], O_RDONLY) <= 0)
			return (1);
		sphere->path = line[1];
		return (0);
	}
	else
		return (1);
}

void	get_texture(t_scene *scene)
{
	t_figure *tmp;

	tmp = scene->figure;
	while (tmp)
	{
		if (tmp->type == SPHERE && tmp->sphere->has_texture == true)
		{
			tmp->sphere->texture.img_ptr = mlx_xpm_file_to_image(scene->mlx->mlx,
				tmp->sphere->path, &tmp->sphere->texture.width, &tmp->sphere->texture.height);
			if (!tmp->sphere->texture.img_ptr)
			{
				err("no xpm");//avelacnel freenry
				exit(777);
			}
			tmp->sphere->texture.img_pixels_ptr = mlx_get_data_addr(tmp->sphere->texture.img_ptr,
					&tmp->sphere->texture.bits_per_pixel, &tmp->sphere->texture.line_len,
					&tmp->sphere->texture.endian);
		}
		tmp = tmp->next;
	}
}

void	get_sphere_uv(t_sphere *sphere, t_vector point, double *u, double *v)
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

t_color	get_texture_color(t_img *texture, double u, double v)
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

int	init_bump(char *bmp, t_sphere *sphere)
{
	char	**line;
	
	if (!bmp || !sphere)
		return (1);
	line = split_char(bmp, ':');
	if (!(ft_strcmp(line[0], "bmp")))
	{
		sphere->has_bump = true;
		sphere->bmp_map = line[1];
		return (0);
	}
	else
		return (1);
}

void	get_bmp(t_scene *scene)
{
	t_figure *tmp = scene->figure;
	while (tmp)
	{
		if (tmp->sphere->has_bump == true)
		{
			tmp->sphere->bump.img_ptr = mlx_xpm_file_to_image(scene->mlx->mlx,
				tmp->sphere->bmp_map, &tmp->sphere->bump.width, &tmp->sphere->bump.height);
			if (!tmp->sphere->bump.img_ptr)
				err("no bmp\n");
			tmp->sphere->bump.img_pixels_ptr = mlx_get_data_addr(tmp->sphere->bump.img_ptr,
					&tmp->sphere->bump.bits_per_pixel, &tmp->sphere->bump.line_len,
					&tmp->sphere->bump.endian);
			printf("%s\n",tmp->sphere->path);
		}
		tmp = tmp->next;
	}
	
}
