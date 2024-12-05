/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:27:57 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/03 17:26:42 by marvin           ###   ########.fr       */
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
	default_init_fig(figure);///
	// figure->sphere = NULL;
	// figure->plane = NULL;
	// figure->cylinder = NULL;
	// figure->specular = 100.0;
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

t_figure	*ft_lstlast_figure(t_figure *figure)
{
	if (figure == NULL)
		return (NULL);
	while
	 (figure && figure->next)
		figure = figure->next;
	return (figure);
}

t_light	*lst_create_light(t_scene *scene, char **matrix)
{
	t_light	*light;
	
	light = parse_light(matrix, scene);
	light->next = NULL;
	return (light);
}

void	ft_lstadd_back_light(t_light **lst, t_light *new)
{
	t_light	*ptr;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	ptr = ft_lstlast_light(*lst);
	ptr -> next = new;
}

t_light	*ft_lstlast_light(t_light *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}
