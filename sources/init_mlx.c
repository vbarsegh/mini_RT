/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:31:32 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/07 20:40:04 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_mlx(t_scene *scene)
{
	scene->mlx = (t_mlx_vars *)malloc(sizeof(t_mlx_vars));
	scene->img = (t_img *)malloc(sizeof(t_img));
	scene->mlx->mlx = mlx_init();
	if (scene->mlx->mlx == NULL)
		err("MLX initialization failed!\n");
	scene->mlx->win = mlx_new_window(scene->mlx->mlx,
			scene->width, scene->height, "miniRT");
	if (scene->mlx->win == NULL)
		err("MLX connection failed!\n");
	scene->img->img_ptr = mlx_new_image(scene->mlx->mlx, WIDTH, HEIGHT);
	scene->img->img_pixels_ptr = mlx_get_data_addr(scene->img->img_ptr, \
		&scene->img->bits_per_pixel,
			&scene->img->line_len, &scene->img->endian);
	scene->img->width = scene->width;
	scene->img->height = scene->height;
	// t_figure *tmp = scene->figure;
	// while (tmp)
	// {
		get_texture(scene);
		
	// 	tmp = tmp->next;
	// }
	ray_tracing(scene);
	mlx_put_image_to_window(scene->mlx->mlx,
		scene->mlx->win, scene->img->img_ptr, 0, 0);
	mlx_hook(scene->mlx->win, 2, 0, &handler, scene);
	mlx_hook(scene->mlx->win, 17, 0, &mouse_close, scene);
	mlx_loop_hook(scene->mlx->mlx, &draw, scene);
	// // //system("leaks miniRT");	
	mlx_loop(scene->mlx->mlx);
	//system("leaks miniRT");
}

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

