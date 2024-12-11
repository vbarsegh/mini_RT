/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:44:02 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/11 15:44:06 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	fooo2(char *str, int i)
{
	int	count;

	while (str[i])
	{
		count = 0;
		while (str[i] && str[i] != ',')
		{
			if (str[i] == '.')
				count++;
			i++;
		}
		if (count > 1)
			return (-1);
		if (str[i])
			i++;
	}
	return (1);
}

int	fooo(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '.')
		return (-1);
	i++;
	while (str[i])
	{
		if (str[i] == '.')
			if (!(str[i + 1] >= '0' && str[i + 1] <= '9')
				|| !(str[i - 1] >= '0' && str[i - 1] <= '9'))
				return (-1);
		i++;
	}
	i = 0;
	return (fooo2(str, i));
}
