/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:07:48 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/06 22:58:09 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	main_a(int ac, char **av)
{
	t_scene	*scene;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (1);
	init_scene(scene);
	if (validation(ac, av, scene) == 0)
	{
		init_mlx(scene);
		free_scene_members(scene);
		//system("leaks miniRT");
		return (0);
	}
	free_scene_members(scene);
	// //system("leaks miniRT");
	return (1);
}

int	main(int ac, char **av)
{
	main_a(ac, av);
	//system("leaks miniRT");
}

void	free_scene_members(t_scene *scene)
{
	if (scene->camera)
		free_cam(scene);
	if (scene->ambient)
		free_ambient(scene);
	if (scene->light)
	{
		free_list_of_light(scene->light);
		scene->light = NULL;
	}
	if (scene->figure)
	{
		free_list_of_figure(scene->figure);
		scene->figure = NULL;
	}
	if (scene->vplane)
	{
		free(scene->vplane);
		scene->vplane = NULL;
	}
	free(scene->mlx);
	free(scene->img);
	free(scene);
	scene = NULL;
}

void	init_scene(t_scene *scene)
{
	scene->camera = NULL;
	scene->ambient = NULL;
	scene->light = NULL;
	scene->figure = NULL;
	scene->vplane = NULL;
	scene->i = 0;
	scene->j = 0;
	scene->ray = new_vector(0, 0, 0);
	scene->mlx = NULL;
	scene->img = NULL;
	scene->width = WIDTH;
	scene->height = HEIGHT;
	scene->count.count_ambient = 0;
	scene->count.count_camera = 0;
}
