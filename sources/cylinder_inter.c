/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 18:25:01 by vbarsegh          #+#    #+#             */
/*   Updated: 2024/12/06 13:36:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	solve_cylinder(t_vector pos, t_vector ray, t_figure *obj, t_math *dot)//stuguma hatum ka bakavoy hartutyan het
{
	t_vector	v;
	t_vector	u;
	t_vector	vec;

	obj->point.dist = 0;
	vec = vec_subtract(pos, obj->cylinder->center);
	v = vec_subtract(ray, num_product_vect(obj->cylinder->orient,
				vec_dot_product(obj->cylinder->orient, ray)));
	u = vec_subtract(vec, num_product_vect(obj->cylinder->orient,
				vec_dot_product(obj->cylinder->orient, vec)));
	dot->a = vec_dot_product(v, v);
	dot->b = 2 * vec_dot_product(v, u);
	dot->c = vec_dot_product(u, u) - pow(obj->cylinder->radius, 2);
	dot->disc = pow(dot->b, 2) - 4 * dot->a * dot->c;
	if (dot->disc < 0)
		return ;
	dot->x1 = ((dot->b * (-1)) - sqrt(dot->disc)) / (2 * dot->a);
	dot->x2 = ((dot->b * (-1)) + sqrt(dot->disc)) / (2 * dot->a);
	find_hit_distance(&obj, *dot);
}

double	check_caps(t_vector pos, t_vector ray, t_figure *obj, t_math *dot)
{
	double	dist;

	dist = 0;
	obj->point.inter_pos = sum_vect(pos, num_product_vect(ray,
				obj->point.dist));
	dot->m1 = vec_dot_product(obj->cylinder->orient,
			vec_subtract(obj->point.inter_pos, obj->cylinder->center));//показывает, насколько далеко по оси цилиндра находится точка пересечения. расстояние(visota) от центра нижней крышки до точки пересечения
	dot->m2 = vec_dot_product(obj->cylinder->orient,
			vec_subtract(obj->point.inter_pos, obj->cylinder->center1));//Эти значения представляют проекцию точки пересечения на ось цилиндра.
	if (dot->m1 > 0 && dot->m2 < 0)//чтобы проверить, попадает ли точка пересечения в область между верхней и нижней крышками:kam senc::Гарантирует, что пересечение происходит в пределах высоты цилиндра.
		dist = obj->point.dist;
	return (dist);
}

int	solve_caps(t_vector pos, t_vector ray, t_figure *obj)
{
	t_vector	surf;
	t_math		p;

	p.x1 = caps_inter(pos, ray, obj->cylinder->orient, obj->cylinder->center);
	p.x2 = caps_inter(pos, ray, obj->cylinder->orient, obj->cylinder->center1);
	if (p.x1 == INFINITY && p.x2 == INFINITY)
		return (0);
	obj->point.dist = p.x1;
	if (p.x1 > p.x2)
	{
		obj->cylinder->flag = 1;//hatum verevi krishkayi het,0-i depqum takini het
		obj->point.dist = p.x2;
	}
	obj->point.inter_pos = sum_vect(pos, num_product_vect(ray,
				obj->point.dist));
	if (obj->cylinder->flag)
		surf = vec_subtract(obj->point.inter_pos, obj->cylinder->center1);
	else
		surf = vec_subtract(obj->point.inter_pos, obj->cylinder->center);
	if (vec_dot_product(surf, surf) < pow(obj->cylinder->radius, 2))//Если длина surf меньше радиуса цилиндра, то точка пересечения находится внутри крышки.
	{
		obj->cylinder->cap = 1;// Пересечение с крышкой
		return (1);
	}
	return (0);
}

double	cylinder_intersection(t_vector pos, t_vector ray, t_figure *obj)
{
	double	dist;
	t_math	dot;

	obj->cylinder->cap = 0;
	obj->cylinder->flag = 0;
	solve_cylinder(pos, ray, obj, &dot);
	dist = check_caps(pos, ray, obj, &dot);
	if (solve_caps(pos, ray, obj))
	{
		if (dist && dist < obj->point.dist && dot.m1 > 0 && dot.m2 < 0)
		{
			obj->point.dist = dist;
			obj->cylinder->cap = 0;
		}
		return (obj->point.dist);
	}
	if (dot.m1 > 0 && dot.m2 < 0)
	{
		obj->point.dist = dist;
		obj->point.inter_pos = sum_vect(pos, num_product_vect(ray,
					obj->point.dist));
		return (obj->point.dist);
	}
	return (INFINITY);
}

double	caps_inter(t_vector pos, t_vector ray, t_vector norm, t_vector center)//В общем, функция caps_inter проверяет, пересекает ли луч крышку цилиндра и, если пересекает, вычисляет точку пересечения на крышке.
{
	double		dist;
	double		dot;
	t_vector	vec;

	dist = 0;
	dot = vec_dot_product(norm, ray);
	if (fabs(dot) < __FLT_EPSILON__)
		return (INFINITY);
	vec = vec_subtract(center, pos);
	dist = vec_dot_product(norm, vec) / dot;
	if (dist < __FLT_EPSILON__)//Если это скалярное произведение близко к нулю (то есть луч параллелен крышке), то пересечения не будет, и функция возвращает INFINITY.
		return (INFINITY);
	return (dist);
}


// cylinder->center: Центр основания цилиндра (нижнего круга). Это начальная точка цилиндра, которая задается при создании объекта цилиндра.

// cylinder->orient: Вектор ориентации цилиндра. Он задает направление вдоль оси цилиндра (нормализованный вектор).

// cylinder->height: Высота цилиндра, задающая расстояние между нижним и верхним кругами.

// num_product_vect(cylinder->orient, cylinder->height): Умножает вектор ориентации цилиндра (cylinder->orient) на его высоту (cylinder->height). Это вектор, указывающий из центра нижнего круга (основания) в центр верхнего круга.

// sum_vect(cylinder->center, ...): Прибавляет этот вектор к центру нижнего круга (cylinder->center), чтобы получить координаты центра верхнего круга (cylinder->center1).

// Vardan, [06.12.2024 12:03]
// flag
// Этот параметр используется, чтобы определить, пересечение произошло с верхней крышкой цилиндра или с нижней.
// Значения:
// 0: Пересечение с нижней крышкой.
// 1: Пересечение с верхней крышкой.

// Vardan, [06.12.2024 12:04]
// cap
// Этот параметр указывает, пересечение произошло с крышкой цилиндра (верхней или нижней) или с боковой поверхностью.
// Значения:
// 0: Пересечение с боковой поверхностью цилиндра.
// 1: Пересечение с одной из крышек (верхней или нижней).

// Vardan, [06.12.2024 12:08]
// В коде переменная surf представляет собой вектор, который указывает направление от точки пересечения луча с цилиндром к центру крышки (верхней или нижней). Этот вектор используется для проверки, находится ли точка пересечения внутри радиуса цилиндра (на крышке) или нет.

// solve_cylinder определяет точки пересечения луча с боковой поверхностью цилиндра, решая квадратное уравнение. Основные этапы:

// Определение вспомогательных векторов:

// vec: разница между начальной точкой луча (pos) и центром цилиндра (obj->cylinder->center).
// v: направление луча, исключая его компоненту вдоль ориентации цилиндра (obj->cylinder->orient).
// u: вектор от начальной точки луча до цилиндра, исключая компоненту вдоль оси цилиндра.

// x1 և x2 արմատները գտնելուց հետո լրացուցիչ ստուգվում է
//  թե արդյոք այդ հատման կետերը գտնվում են մխոցի բարձրության մեջ (սահմանափակված m1 և m2):