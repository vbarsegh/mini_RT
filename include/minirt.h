/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbarsegh <vbarsegh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:22:05 by aeminian          #+#    #+#             */
/*   Updated: 2024/12/08 14:56:01 by vbarsegh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
#  define ESC	53
#  define LEFT	123
#  define RIGHT	124
#  define DOWN	125
#  define UP	126
#  define A	0
#  define S	1
#  define D	2
#  define W	13
# define WIDTH 1000
# define HEIGHT 700
# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include "../include/mlx.h"
# include "../include/get_next_line.h"

// # ifdef __linux__
// #  define ESC	65307
// #  define LEFT	65361
// #  define RIGHT	65363
// #  define DOWN	65364
// #  define UP	65362
// #  define A	97
// #  define S	115
// #  define D	100
// #  define W	119
// #  define C	99
// #  define T	116
// #  define B	98
// # else
// #  define ESC	53
// #  define LEFT	123
// #  define RIGHT	124
// #  define DOWN	125
// #  define UP	126
// #  define A	0
// #  define S	1
// #  define D	2
// #  define W	13
// #  define C	8
// #  define T	17
// #  define B	11
// # endif

typedef enum e_figure_type
{
	CYLINDER,
	SPHERE,
	PLANE,
}	t_type;

typedef struct n_img
{
	void	*img_ptr;//pixelnerov stacvac yndhanur nkari hascena
	char	*img_pixels_ptr;//pixeli hascena
	int		bits_per_pixel;//mi piqselyb te qani bita zbaxecnum
	int		endian;
	int		line_len;//plangi erkarutyan vra qani pixela texavorvum
	int		height;//ha vor?
	int		width;//ha vor?
}	t_img;

typedef struct s_atof
{
	double	num;
	double	fraction;
	int		sign;
	int		is_double;
	int		i;
}	t_atof;

typedef struct s_mlx_vars
{
	void	*mlx;
	void	*win;
}	t_mlx_vars;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}	t_color;

typedef struct s_ambient
{
	double intensity;
	double	ratio_lighting;
	t_color	light;
	int		count;
}	t_ambient;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
	double	w;//chgitem xi,karoxa vor matricy 4*4a dra ahamar?
}	t_vector;

typedef struct s_camera
{
	t_vector	center;
	t_vector	direction;//uxxutyun
	double		fov;//size_t,կհաշվարկի տեսադաշտի լայնությունը
	int		count;//petqa?
}	t_camera;

typedef struct s_light
{
	t_vector		coords;
	double			brightness;
	t_color			color;
	struct s_light	*next;
}	t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		radius;
	t_color		color;
	t_img 		texture;
	t_img 		bamp;
	bool		has_texture;
	bool		has_bamp;
	char		*path;
	char		*bmp_map;
}	t_sphere;

typedef struct s_plane
{
	t_vector	coords;//center
	t_color		color;
	t_vector	orient;//uxxutyun,planei hamar ira uxxutyuny u normal@ hamynknum en kam -uxxutyuna normaly
}	t_plane;

typedef struct s_cylinder
{
	t_vector	center;//nerqevi shrjani (krujoki) kentronna
	t_vector	orient;//arancqna
	t_vector	center1;//verevi shrjani (krujoki) kentronna
	double		radius;
	double		height;
	int			cap;
	int			flag;
	t_color		color;
}	t_cylinder;

typedef struct s_math
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	x1;
	double	x2;
	double	m1;
	double	m2;
}	t_math;

typedef struct s_matrix
{
	double	m[4][4];
}	t_matrix;

typedef struct s_crossing
{
	double		dist;
	t_vector	inter_pos;//hit_pos
	t_vector	inter_normal_vec;//verevini normal@
}				t_crossing;

typedef struct s_figure
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_color			color;
	t_type			type;
	t_crossing		point;
	double			specular;
	struct s_figure	*next;
}	t_figure;

typedef struct s_hatum
{
	double		dot;
	t_figure	*figure;
}	t_hatum;

typedef struct s_vplane
{
	int		mlx_x;
	int		mlx_y;
	double	width;
	double	height;
	double	pixel_x;
	double	pixel_y;
	double	x_angle;
	double	y_angle;
}	t_vplane;

typedef struct s_count
{
	int	count_ambient;
	int	count_camera;
} t_count;

typedef struct s_scene
{
	t_camera	*camera;
	t_ambient	*ambient;
	t_light		*light;
	t_figure	*figure;
	t_vplane	*vplane;
	t_mlx_vars	*mlx;
	t_img		*img;//data
	t_vector	ray;
	t_count		count;
	double		width;
	double		height;
	int			i;
	int			j;
}	t_scene;

/////////////////exit_free////////////////////////
int			err(char *str);
void		exit_and_free_str(char *str_free, char *str_err, t_scene *scene);
void		exit_and_free_matrix(char **map, char *str_err, t_scene *scene);
void		exit_and_free(char **map, char *str_err, t_scene *scene, char **matrix);
void		free_matrix(char **matrix);
void		free_scene_members(t_scene *scene);
void		free_list_of_light(t_light *light);
void		free_list_of_figure(t_figure *figure);
void		free_cam(t_scene *scene);
void		free_ambient(t_scene *scene);

/////////////////parsing//////////////////////////////
void		parsing(char **map, t_scene *scene);
t_light		*parse_light(char **matrix, t_scene *scene);
t_sphere	*parse_sphere(char **matrix, t_scene *scene);
t_cylinder	*parse_cylinder(char **matrix, t_scene *scene);
t_plane		*parse_plane(char **matrix, t_scene *scene);

/////////////////parsing_utils////////////////////////
void		found_what_scene_is_it(char **matrix, t_scene *scene);
void		*parse_camera(char **matrix, t_scene *scene);
void		*parse_ambient(char **matrix, t_scene *scene);

/////////////////init_mlx////////////////////////////
void		init_mlx(t_scene *scene);
void		init_scene(t_scene *scene);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);

/////////////////utils///////////////////////////////
int			malloc_check(char *s);
int			check1(char c, char const *set);
int			is_white_space(char c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strstr_alt(char *str, char *to_find);
int			only_trim_simbols(char *str);
int			cur_line_is_com(char *str);

/////////////////utils2/////////////////////////////
long long			ft_atoi(const char *str);
int 		if_char_and_digit(char *line, char c);
int			matrix_row(char **matrix);
double		ft_atof(char *str);
int			if_only_digit(char *line);
int			if_str_and_digit(char *line, char *set);
int			have_this_char_in_set(char c, char *set);
char		*ft_strchr(const char *s, int c);
int			only_new_line_or_spaces(char *res);

/////////////////validation////////////////////////
int			validation(int ac, char **av, t_scene *scene);
int			is_rt(char *str);
int			checkk(char *str);
/////////////////init_func////////////////////////////
void		init_coords(t_vector *coords, char **matrix, t_scene *scene, int i);
void		init_color(t_color *color, char **matrix, t_scene *scene, int i);
void		init_orient(t_vector *orient, char **matrix, t_scene *scene, int i);

/////////////////split_char////////////////////////////
int			foo_sum_tar_(char const *s, char c);
int			func_count_word_(const char *s, char c);
char		**split_char(char const *s, char c);
int			ft_strlen(const char *str);

/////////////////split////////////////////////////
int			check_00(char **arr, const char *s, int count);
char		**split(char const *s);

/////////////////trim////////////////////////////
char		*strtrim_end(char *str);
char		*ft_strtrim(char *s1, char *set);

/////////////////gnl////////////////////////////
char		*ft_strdup(char *s);
char		*ft_strjoin(const char *s1, const char *s2);
char		*ft_strchr_gnl(const char *str, int c);

/////////////////key_hooks////////////////////////////
int			handler(int keysym, t_scene *scene);
int			mouse_close(t_scene *scene);

/////////////////list_functions////////////////////////////
void		default_init_fig(t_figure *figure);
t_light		*lst_create_light(t_scene *scene, char **matrix);
void		ft_lstadd_back_light(t_light **lst, t_light *new);
t_light		*ft_lstlast_light(t_light *lst);
t_figure	*lst_create_figure(t_scene *scene, char **matrix, int type);
void		ft_lstadd_back_figure(t_figure **figure, t_figure *new);
t_figure	*ft_lstlast_figure(t_figure *figure);

/////////////////vector.c////////////////////////////
t_vector	new_vector(double x, double y, double z);
t_vector	vec_subtract(t_vector vec1, t_vector vec2);
double		vec_length(t_vector vec);
double		vec_dot_product(t_vector vec1, t_vector vec2);
void		vec_normalize(t_vector *vec);
double		vec_dot_product(t_vector vec1, t_vector vec2);
t_vector	num_product_vect(t_vector vec, double num);
t_vector	sum_vect(t_vector v1, t_vector v2);
double		dist_vect(t_vector v1, t_vector v2);
t_vector	vec_cross_product(t_vector vec1, t_vector vec2);

//////////////////color_functions.c/////////////////////
t_color		calc_rgb_light(t_color col, double ratio);
int			rgb_color_to_hex(t_color rgb);
t_color		add_rgb_light(t_color a, t_color b);
t_color		new_color(int r, int g, int b);
t_color		multiply_rgbs(t_color a, t_color b);

/////////////////ray_tracing.c////////////////////////////
void		ray_tracing(t_scene *scene);
void		get_pixel_color(int *color, t_figure *obj, t_scene *scene);
t_vplane	*get_view_plane(t_scene *scene);////ray_tracing_2.c
double		sphere_intersect(t_vector center, t_vector ray, t_figure *obj);
double		plane_inter(t_vector pos, t_vector ray, t_figure *obj);
double		closest_inter(t_vector pos, t_vector ray, t_figure *figure, t_figure **tmp);
int			color_in_current_pixel(t_scene *scene);
void		find_hit_distance(t_figure **obj, t_math dot);

//////////////cylinder.c//////////////
double		cylinder_intersection(t_vector pos, t_vector ray, t_figure *obj);
double		caps_inter(t_vector pos, t_vector ray, t_vector norm, t_vector center);

void		_rotate_(int keypress, t_scene *scene);
void		_move_(int keypress, t_scene *scene);
void		_rotate_(int keypress, t_scene *scene);
int			draw(t_scene *scene);
void		rotate_scene_up(t_scene *scene);
void		rotate_scene_left(t_scene *scene);
void		rotate_scene_right(t_scene *scene);
void		rotate_scene_down(t_scene *scene);

void		rotate_sphere(t_sphere *sph, t_matrix matrix);
void		rotate_plane(t_plane *plane, t_matrix matrix);
void		rotate_light(t_light *light, t_matrix matrix);
void		rotate_cylinder(t_cylinder *cylinder, t_matrix matrix);

t_matrix	get_rotation_z(double angle);
t_matrix	get_rotation_y(double angle);
t_matrix	get_rotation_x(double angle);

t_vector	multi_mat_vect(t_matrix m, t_vector v);
t_matrix	new_zero_matrix(void);
void		init_scene(t_scene *scene);

/////////////////compute_light.c/////////////////
t_color		compute_light(t_scene *scene, t_figure *obj, t_color *specular);
void		set_inter_normal_vec(t_scene *scene, t_figure *obj);
void		calculate_sph_norm(t_figure *obj);
void		calculate_plane_norm(t_figure *obj, t_vector ray);
t_color		diffuse_light(t_figure *obj, t_light *light_fig);
t_color		specular_light(t_scene *scene, t_light *light_fig, t_figure *obj);
void		set_inter_normal_vec(t_scene *scene, t_figure *obj);
t_vector	reflect_ray(t_vector light, t_vector p_normal);
t_color		diffuse_light(t_figure *obj, t_light *light);
t_color		specular_light(t_scene *scene, t_light *light, t_figure *obj);
t_vector	reflect_ray(t_vector ray, t_vector p_normal);

/////////////////////shadow.c/////////////////
int			compute_shadow(t_scene *scene, t_figure *obj, t_light *light);
int			in_shadow(t_scene *scene, t_vector ray, t_light	*light, \
	t_figure **obj);
t_vector	look_at(t_scene	*scene, double ray_x, double ray_y);
double		closest_inter_dlya_shadow(t_vector pos, t_vector ray, t_figure *figure);

//init_texture
int	init_texture(char *xpm, t_sphere *sphere);
void	get_texture(t_scene *scene);
t_vector vector_normalize(t_vector v);
t_color get_texture_color(t_img *texture, double u, double v);
void get_sphere_uv(t_sphere *sphere, t_vector point, double *u, double *v);
int color_in_current_pixel2(t_scene *scene);
t_vector vec_scale(t_vector v, double scalar);
t_color create_color(double r, double g, double b);
int create_int_from_color(t_color color);
t_color default_shading(t_scene *scene, t_figure *figure);
t_vector bump_normal(t_sphere *sphere, t_vector normal, double u, double v);
// int	init_bump(char *bmp, t_sphere *sphere);
void	get_bmp(t_scene *scene);
#endif
