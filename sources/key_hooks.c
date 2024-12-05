/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:13:51 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/05 16:49:10 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	handler(int keypress, t_scene *scene)
{
	printf("%d\n", keypress);
	if (keypress == ESC)
	{
		mlx_destroy_image(scene->mlx->mlx, scene->img->img_ptr);
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		exit(0);
	}
	if (scene->figure && scene->camera && scene->ambient)
	{
		if (keypress == A || keypress == S || keypress == D || keypress == W)
		{
			
			_rotate_(keypress, scene);
		}
		if (keypress == ESC)
		{
			mlx_destroy_image(scene->mlx->mlx, scene->img->img_ptr);
			mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
			mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
			exit(0);
		}
	}
	return (0);
}

int	mouse_close(t_scene *scene)
{
	mlx_destroy_image(scene->mlx->mlx, scene->img->img_ptr);
	mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
	mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
	exit(0);//lavem are vor pakelem?
	return (0);
}