/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 23:49:19 by adel              #+#    #+#             */
/*   Updated: 2024/12/09 15:01:18 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	texture(char **matrix, t_sphere	*sphere, t_scene *scene)
{
	if (matrix[4] || matrix[5])
	{
		if (matrix[4] && init_texture(matrix[4], sphere))
			exit_and_free_matrix(matrix, "Error: invalid xpm", scene);
		if (matrix[5] && init_texture(matrix[4], sphere))
			exit_and_free_matrix(matrix, "Error: invalid xpm", scene);
	}
}

void	geting_texture(t_scene *scene)
{
	if (scene->figure->type == SPHERE && scene->figure->sphere->has_texture)
		get_xpm(scene);
	if (scene->figure->type == SPHERE && scene->figure->sphere->has_bump)
		get_bmp(scene);
}

void	get_xpm(t_scene *scene)
{
	t_figure	*tmp;

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
				exit(1);
			}
			tmp->sphere->texture.img_pixels_ptr = mlx_get_data_addr(tmp->sphere->texture.img_ptr,
					&tmp->sphere->texture.bits_per_pixel, &tmp->sphere->texture.line_len,
					&tmp->sphere->texture.endian);
		}
		tmp = tmp->next;
	}
}

void	get_bmp(t_scene *scene)
{
	t_figure	*tmp;

	tmp = scene->figure;
	while (tmp)
	{
		if (tmp->type == SPHERE && tmp->sphere->has_bump == true)
		{
			tmp->sphere->bump.img_ptr = mlx_xpm_file_to_image(scene->mlx->mlx,
				tmp->sphere->bmp_map, &tmp->sphere->bump.width, &tmp->sphere->bump.height);
			if (!tmp->sphere->bump.img_ptr)
			{
				err("no bmp");//avelacnel freenry
				exit(1);
			}
			tmp->sphere->bump.img_pixels_ptr = mlx_get_data_addr(tmp->sphere->bump.img_ptr,
					&tmp->sphere->bump.bits_per_pixel, &tmp->sphere->bump.line_len,
					&tmp->sphere->bump.endian);
		}
		tmp = tmp->next;
	}
}
