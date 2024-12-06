/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 14:53:05 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/06 18:57:03 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	ft_check_minimum_requirements(t_scene *scene, char **map)
{
	if (!scene->camera || scene->count.count_camera != 1)
	{
		free_matrix(map);
		free_scene_members(scene);
		//system("leaks miniRT");
		write (1, "Requirement: non existing camera or count is not 1\n", 51);
		exit(11);
	}
	if (!scene->ambient || scene->count.count_ambient != 1)
	{
		free_matrix(map);
		free_scene_members(scene);
		//system("leaks miniRT");
		write (1,
			"Requirement: non existing ambient light or count is not 1\n", 58);
		exit(11);
	}
	if (!scene->light)
	{
		free_matrix(map);
		free_scene_members(scene);
		//system("leaks miniRT");
		write (1, "Requirement: non existing light\n", 32);
		exit(11);
	}
}

void	parsing(char **map, t_scene *scene)
{
	int		i;
	char	**matrix;

	i = 0;
	while (map[i])
	{
		matrix = split(map[i]);
		found_what_scene_is_it(matrix, scene);
		free_matrix(matrix);
		matrix = NULL;
		i++;
	}
	ft_check_minimum_requirements(scene, map);
		//system("leaks miniRT");
}

t_cylinder	*parse_cylinder(char **matrix, t_scene *scene)
{
	int			i;
	t_cylinder	*cylinder;

	i = 0;
	cylinder = malloc(sizeof(t_cylinder));
	if (matrix_row(matrix) != 6)
		exit_and_free_matrix(matrix,"Error: wrong qanaki arguments for cylinder", scene);
	while (matrix[++i])
	{
		if (matrix[i][0] == ',' || matrix[i][ft_strlen(matrix[i]) - 1] == ','
			|| (ft_strstr_alt(matrix[i], ",,")))
			exit_and_free_matrix(matrix,"Error: bad arguments cy", scene);
	}
	init_coords(&cylinder->center, matrix, scene, 1);
	init_orient(&cylinder->orient, matrix, scene, 2);
	if (if_char_and_digit(matrix[3], '.') == -1)
		exit_and_free_matrix(matrix, "Error: bad simbols for cylinder diametr", scene);
	cylinder->radius = ft_atof(matrix[3]) / 2;
	if (if_char_and_digit(matrix[4], '.') == -1)
		exit_and_free_matrix(matrix, "Error: bad simbols for cylinder height", scene);
	cylinder->height = ft_atof(matrix[4]);
	init_color(&cylinder->color, matrix, scene, 5);
	cylinder->center1 = sum_vect(cylinder->center, \
		num_product_vect(cylinder->orient, cylinder->height));
	return (cylinder);
}

t_plane	*parse_plane(char **matrix, t_scene *scene)
{
	int		i;
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	i = 0;
	if (matrix_row(matrix) != 4)
		exit_and_free_matrix(matrix,
			"Error: wrong qanaki arguments for plane", scene);
	while (matrix[++i])
	{
		if (matrix[i][0] == ',' || matrix[i][ft_strlen(matrix[i]) - 1] == ','
			|| (ft_strstr_alt(matrix[i], ",,")))
			exit_and_free_matrix(matrix, "Error: bad arguments pl", scene);
	}
	init_coords(&plane->coords, matrix, scene, 1);
	init_orient(&plane->orient, matrix, scene, 2);
	init_color(&plane->color, matrix, scene, 3);
	return (plane);
}

t_sphere	*parse_sphere(char **matrix, t_scene *scene)
{
	int			i;
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	i = 0;
	if (!(matrix_row(matrix) > 3 && matrix_row(matrix) < 7))
		exit_and_free_matrix(matrix,
			"Error: wrong arguments for sphere", scene);
	while (matrix[++i])
	{
		if (matrix[i][0] == ',' || matrix[i][ft_strlen(matrix[i]) - 1] == ','
			|| (ft_strstr_alt(matrix[i], ",,")))
			exit_and_free_matrix(matrix, "Error: bad arguments sp", scene);
	}
	init_coords(&sphere->center, matrix, scene, 1);
	if (if_char_and_digit(matrix[2], '.') == -1)
		exit_and_free_matrix(matrix, "Error: bad simbols for sphere", scene);
	sphere->radius = ft_atof(matrix[2]) / 2;
	init_color(&sphere->color, matrix, scene, 3);
	if (init_texture(matrix[4], sphere))
		exit_and_free_matrix(matrix, "Error: invalid xpm", scene);
	return (sphere);
}

t_light	*parse_light(char **matrix, t_scene *scene)
{
	int		i;
	t_light	*light;

	light = malloc(sizeof(t_light));
	i = 0;
	if (matrix_row(matrix) != 4)
		exit_and_free_matrix(matrix,
			"Error: wrong qanaki arguments for light coordinates", scene);
	while (matrix[++i])
	{
		if (matrix[i][0] == ',' || matrix[i][ft_strlen(matrix[i]) - 1] == ','
			|| (ft_strstr_alt(matrix[i], ",,")))
			exit_and_free_matrix(matrix, "Error: bad arguments L", scene);
	}
	init_coords(&light->coords, matrix, scene, 1);
	if (if_char_and_digit(matrix[2], '.') == -1)
		exit_and_free_matrix(matrix,
			"Error: bad simbols for light brightness", scene);
	light->brightness = ft_atof(matrix[2]);
	if (!(light->brightness >= 0.0 && light->brightness <= 1.0))
		exit_and_free_matrix(matrix,
			"Error: bad value for light brightness", scene);
	init_color(&light->color, matrix, scene, 3);
	return (light);
}
