/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:56:26 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/02 17:02:37 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	write(2, "\n", 1);
	return (1);
}

void	exit_and_free_str(char *str_free, char *str_err ,t_scene *scene)
{
	err(str_err);
	free (str_free);
	free_scene_members(scene);
	system("leaks miniRT");
	exit (1);
}

void	exit_and_free_matrix(char **map, char *str_err, t_scene *scene)
{
	free_matrix(map);
	err(str_err);
	free_scene_members(scene);
	system("leaks miniRT");
	exit(1);
}

void	exit_and_free(char **map, char *str_err, t_scene *scene, char **matrix)
{
	free_matrix(matrix);
	exit_and_free_matrix(map, str_err, scene);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	free_list_of_light(t_light *light)//check Nar
{
	t_light	*tmp;

	while (light)
	{
		tmp = light;
		light = light->next;
		free(tmp);
	}
}

void	free_list_of_figure(t_figure *figure)//check Nar
{
	t_figure	*tmp;

	while (figure)
	{
		tmp = figure;
		if (tmp->sphere)
			free(tmp->sphere);
		if (tmp->plane)
			free(tmp->plane);
		if (tmp->cylinder)
			free(tmp->cylinder);
		figure = figure->next;
		free(tmp);
	}
}

void	free_cam(t_scene *scene)
{
	free(scene->camera);
	scene->camera = NULL;
}

void	free_ambient(t_scene *scene)
{
	free(scene->ambient);
	scene->ambient = NULL;
}