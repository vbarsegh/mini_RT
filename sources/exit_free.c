/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 20:56:26 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/05 15:42:51 by adel             ###   ########.fr       */
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