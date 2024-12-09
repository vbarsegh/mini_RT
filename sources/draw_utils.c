/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel <adel@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 01:04:47 by adel              #+#    #+#             */
/*   Updated: 2024/12/09 18:10:06 by adel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int	draw(t_scene *scene)
{
	scene->img->img_ptr = mlx_new_image(scene->mlx->mlx, WIDTH, HEIGHT);
	scene->img->img_pixels_ptr = mlx_get_data_addr(scene->img->img_ptr, \
	&scene->img->bits_per_pixel, &scene->img->line_len, &scene->img->endian);
	ray_tracing(scene);
	mlx_put_image_to_window(scene->mlx->mlx,
		scene->mlx->win, scene->img->img_ptr, 0, 0);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	char	*addr_end;

	addr_end = img->img_pixels_ptr + (HEIGHT * img->line_len);
	dst = img->img_pixels_ptr
		+(y * img->line_len + x * (img->bits_per_pixel / 8));
	if (dst >= img->img_pixels_ptr && dst < addr_end)
		*(unsigned int *)dst = color;
}


t_vector vec_normalize2(t_vector v) {
    double magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    if (magnitude == 0.0)
        return (t_vector){.x = 0, .y = 0, .z = 0}; // Handle zero-length vector
    return (t_vector){
        .x = v.x / magnitude,
        .y = v.y / magnitude,
        .z = v.z / magnitude
    };
}
void perturb_normal(t_vector *normal, t_vector bump) {
    // Adjust the normal by the bump vector
    *normal = vec_normalize2(sum_vect(*normal, bump));
}
t_color get_texture_color(t_img *texture, double u, double v)
{
    int     x;
    int     y;
    char    *pixel;
    t_color color;
    // Ensure the texture is valid
    if (!texture || !texture->img_pixels_ptr) {
        printf("Error: Invalid texture data\n");
        color.red = 0;   // Default to black color
        color.green = 0;
        color.blue = 0;
        return color;
    }

    // Map texture coordinates to pixel coordinates
    x = (int)(u * texture->width) % texture->width;
    y = (int)(v * texture->height) % texture->height;

    // Ensure x and y are within the texture bounds
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height) {
        printf("Warning: texture coordinates out of bounds (%f, %f)\n", u, v);
        color.red = 0;   // Default to black color
        color.green = 0;
        color.blue = 0;
        return color;
    }

    // Get the pixel pointer
    pixel = texture->img_pixels_ptr + (y * texture->line_len + x * (texture->bits_per_pixel / 8));

    // Assuming the texture is in RGB format (24-bit color)
    color.red = *(unsigned char *)(pixel + 2);
    color.green = *(unsigned char *)(pixel + 1);
    color.blue = *(unsigned char *)(pixel);

    return color;
}

t_color	new_color(int r, int g, int b)
{
	t_color	col;

	col.red = r;
	col.green = g;
	col.blue = b;
	return (col);
}
void	get_pixel_color(int *color, t_figure *obj, t_scene *scene)
{
	t_color	specular;
	t_color	light_in_vec;
	t_color texture_color;
	double u, v;

	if (!obj)
		return ;
	texture_color = obj->color;
	obj->point.inter_pos = sum_vect(scene->camera->center, num_product_vect(scene->ray,
		obj->point.dist));
	set_inter_normal_vec(scene, obj);
	if (obj && obj->type == SPHERE && obj->sphere->has_texture == true)
	{
		t_vector intersection_point = sum_vect(scene->camera->center, vec_scale(scene->ray, obj->point.dist));
		get_sphere_uv(obj->sphere, intersection_point, &u, &v);
		if (obj->sphere->has_texture)
			texture_color = get_texture_color(&obj->sphere->texture, u, v);
		if (obj->sphere->has_bump)
		{
			t_color bump_sample = get_texture_color(&obj->sphere->bump, u, v);
			t_vector bump_vector = color_to_vector(bump_sample);
			perturb_normal(&obj->point.inter_normal_vec, bump_vector);
		}
	}
	*color = rgb_color_to_hex(obj->color);
	specular = new_color(0, 0, 0);
	light_in_vec = compute_light(scene, obj, &specular);
	*color = rgb_color_to_hex(add_rgb_light(multiply_rgbs(light_in_vec, \
		(texture_color)), specular));
}
int	color_in_current_pixel(t_scene *scene)
{
	int			color;
	t_figure	*obj;
	double		closest_dot;


	closest_dot = INFINITY;
	obj = NULL;
	closest_dot = closest_inter(scene->camera->center, scene->ray, scene->figure, &obj);
	
	if (closest_dot == INFINITY)
		color = 0;
	else
		get_pixel_color(&color, obj, scene);
	return (color);
}