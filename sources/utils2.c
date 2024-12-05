/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:46:38 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/05 16:07:50 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	sign;

	sign = 1;
	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - 48);
		i++;
	}
	return (sign * num);
}

int	have_this_char_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (-1);
}

int	matrix_row(char **matrix)
{
	int	row;

	row = 0;
	while (matrix[row])
		row++;
	return (row);
}

int	only_new_line_or_spaces(char *res)
{
	int	i;

	i = 0;
	while(res[i])
	{
		if (res[i] == '\n' || res[i] == 32)
			i++;
		else
			return (-1);
	}
	return (1);
}

int	malloc_check(char *s)
{
	if (!s)
		return(err("Malloc error!"));
	return (0);
}