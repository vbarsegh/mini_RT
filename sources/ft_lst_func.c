/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 16:27:57 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/05 21:00:08 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

t_figure	*ft_lstlast_figure(t_figure *figure)
{
	if (figure == NULL)
		return (NULL);
	while (figure && figure->next)
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
