/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:01:41 by adel              #+#    #+#             */
/*   Updated: 2024/12/06 22:58:09 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	check1(char c, char const *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	is_white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	if_char_and_digit(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 48 && line[i] <= 57) || line[i] == c
			|| line[i] == '-' || line[i] == '+')
			i++;
		else
			return (-1);
	}
	return (1);
}

int	if_str_and_digit(char *line, char *set)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 48 && line[i] <= 57)
			|| have_this_char_in_set(line[i], set) == 1
			|| line[i] == '-' || line[i] == '+')
			i++;
		else
			return (-1);
	}
	return (1);
}

int	if_only_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] >= 48 && line[i] <= 57)
			i++;
		else
			return (-1);
	}
	return (1);
}
