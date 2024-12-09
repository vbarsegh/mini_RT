/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:13:51 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/10 01:15:16 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	handler(int keypress, t_scene *scene)
{
	if (keypress == ESC)
	{
		mlx_destroy_image(scene->mlx->mlx, scene->img->img_ptr);
		mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
		mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		// //system("miniRT leaks");
		exit(0);
	}
	return (0);
}

int	mouse_close(t_scene *scene)
{
	mlx_destroy_image(scene->mlx->mlx, scene->img->img_ptr);
	mlx_clear_window(scene->mlx->mlx, scene->mlx->win);
	mlx_destroy_window(scene->mlx->mlx, scene->mlx->win);
		//system("miniRT leaks");
	exit(0);
	return (0);
}
