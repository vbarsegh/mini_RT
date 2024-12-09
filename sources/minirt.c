/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:07:48 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/09 20:13:41 by adel             ###   ########.fr       */
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
		// t_figure *tmp = scene->figure;
		// while (tmp)
		// {
		// 	if (tmp->type == SPHERE && tmp->sphere->path)
		// 		printf("%s\n", tmp->sphere->path);
		// 	tmp = tmp->next;
		// }
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


