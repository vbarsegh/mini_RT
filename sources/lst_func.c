/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:44:25 by adel              #+#    #+#             */
/*   Updated: 2024/12/05 21:12:09 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	default_init_fig(t_figure *figure)
{
	figure->sphere = NULL;
	figure->plane = NULL;
	figure->cylinder = NULL;
	figure->specular = 100.0;
}

t_figure	*lst_create_figure(t_scene *scene, char **matrix, int type)
{
	t_figure	*figure;

	figure = malloc(sizeof(t_figure));
	if (!figure)
		exit(EXIT_FAILURE);
	default_init_fig(figure);
	if (type == SPHERE)
	{
		figure->sphere = parse_sphere(matrix, scene);
		figure->color = figure->sphere->color;
	}
	else if (type == PLANE)
	{
		figure->plane = parse_plane(matrix, scene);
		figure->color = figure->plane->color;
	}
	else if (type == CYLINDER)
	{
		figure->cylinder = parse_cylinder(matrix, scene);
		figure->color = figure->cylinder->color;
	}
	figure->type = type;
	figure->next = NULL;
	return (figure);
}

void	ft_lstadd_back_figure(t_figure **figure, t_figure *new)
{
	t_figure	*ptr;

	if (!*figure)
	{
		*figure = new;
		return ;
	}
	ptr = ft_lstlast_figure(*figure);
	ptr -> next = new;
}
