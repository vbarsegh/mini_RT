/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:22:00 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/06 22:58:09 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	init_coords(t_vector *coords, char **matrix, t_scene *scene, int i)
{
	char	**split_2_line;

	if (if_str_and_digit(matrix[i], ".,") == -1)
		exit_and_free_matrix(matrix, "Error: bad arguments for camera",
			scene);
	split_2_line = split_char(matrix[1], ',');
	if (!split_2_line)
		exit_and_free_matrix(matrix, "Error: malloc", scene);
	if (matrix_row(split_2_line) != 3)
		exit_and_free(matrix, "Error: bad arguments for camera",
			scene, split_2_line);
	coords->x = ft_atof(split_2_line[0]);
	coords->y = ft_atof(split_2_line[1]);
	coords->z = ft_atof(split_2_line[2]);
	coords->w = 1.0;
	free_matrix(split_2_line);
	//system("leaks miniRT");
}

void	init_orient(t_vector *orient, char **matrix, t_scene *scene, int i)
{
	char	**split_2_line;

	if (if_str_and_digit(matrix[i], ".,") == -1)
		exit_and_free_matrix(matrix, "Error: bad arguments for camera", scene);
	split_2_line = split_char(matrix[i], ',');
	if (!split_2_line)
		exit_and_free_matrix(matrix, "Error: malloc", scene);
	if (matrix_row(split_2_line) != 3)
		exit_and_free(matrix, "Error: bad arguments for camera",
			scene, split_2_line);
	orient->x = ft_atof(split_2_line[0]);
	orient->y = ft_atof(split_2_line[1]);
	orient->z = ft_atof(split_2_line[2]);
	orient->w = 1.0;
	if (!(orient->x >= -1.0 && orient->x <= 1.0)
		|| !(orient->y >= -1.0 && orient->y <= 1.0)
		|| !(orient->z >= -1.0 && orient->z <= 1.0))
		exit_and_free(matrix, "Error: bad value", scene, split_2_line);
	free_matrix(split_2_line);
	//system("leaks miniRT");
	vec_normalize(orient);
}

void	init_color(t_color *color, char **matrix, t_scene *scene, int i)
{
	char	**split_2_line;

	if (if_char_and_digit(matrix[i], ',') == -1)
		exit_and_free_matrix(matrix,
			"Error: bad arguments for ambient1", scene);
	split_2_line = split_char(matrix[i], ',');
	if (!split_2_line)
		exit_and_free_matrix(matrix, "Error: malloc", scene);
	if (matrix_row(split_2_line) != 3)
		exit_and_free(matrix,
			"Error: bad arguments for ambient2", scene, split_2_line);
	if (checkk(split_2_line[0]) == -1 || checkk(split_2_line[1]) == -1
		|| checkk(split_2_line[2]) == -1)
		exit_and_free(matrix,
			"Error: value of color out is range", scene, split_2_line);
	color->red = ft_atoi(split_2_line[0]);
	color->green = ft_atoi(split_2_line[1]);
	color->blue = ft_atoi(split_2_line[2]);
	if (!(color->red >= 0 && color->red <= 255)
		|| !(color->green >= 0 && color->green <= 255)
		|| !(color->blue >= 0 && color->blue <= 255))
		exit_and_free(matrix,
			"Error: value of color out is range", scene, split_2_line);
	free_matrix(split_2_line);
	//system("leaks miniRT");
}

int	checkk(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	// printf("atoi = %lld\n",ft_atoi(str));
	if (i > 11 || ft_atoi(str) > INT_MAX || ft_atoi(str) < INT_MIN)
		return (-1);
	return (1);
}
