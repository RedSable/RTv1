/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:24:06 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 22:43:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int			cone_intersect(t_object obj, t_ray ray, double *t)
{
	double	k;
	t_vec3	oc;
	double	disc;
	t_vec3	coef;

	k = tan(obj.radius / 2 * RAD);
	obj.direction = normalize(obj.direction);
	oc = diff_num(ray.origin, obj.origin);
	coef.x = dot_product(ray.direction, ray.direction) - (1 + k * k) *
	pow(dot_product(ray.direction, obj.direction), 2);
	coef.y = 2 * (dot_product(ray.direction, oc) - (1 + k * k) *
	dot_product(ray.direction, obj.direction) * dot_product(oc, obj.direction));
	coef.z = dot_product(oc, oc) - (1 + k * k) *
	pow(dot_product(oc, obj.direction), 2);
	disc = coef.y * coef.y - 4 * coef.x * coef.z;
	if (disc < 0.0)
		return (0);
	*t = (-coef.y - sqrt(disc)) / (2 * coef.x);
	if (*t < 0.0)
		*t = (-coef.y + sqrt(disc)) / (2 * coef.x);
	if (*t < 0.0)
		return (0);
	return (1);
}

int			cyl_intersect(t_object obj, t_ray ray, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	obj.direction = normalize(obj.direction);
	oc = diff_num(ray.origin, obj.origin);
	a = dot_product(ray.direction, ray.direction) -
	pow(dot_product(ray.direction, obj.direction), 2);
	b = 2 * (dot_product(ray.direction, oc) -
	dot_product(ray.direction, obj.direction) * dot_product(oc, obj.direction));
	c = dot_product(oc, oc) - pow(dot_product(oc, obj.direction), 2)
	- obj.radius * obj.radius;
	disc = b * b - 4 * a * c;
	if (disc < 0.0)
		return (0);
	*t = (-b - sqrt(disc)) / (2 * a);
	if (*t < 0.0)
		*t = (-b + sqrt(disc)) / (2 * a);
	if (*t < 0.0)
		return (0);
	return (1);
}

int			plane_intersect(t_object obj, t_ray ray, double *t)
{
	double	denom;
	t_vec3	a;

	denom = dot_product(ray.direction, obj.direction);
	if (denom != 0.0)
	{
		a = diff_num(obj.origin, ray.origin);
		*t = dot_product(a, obj.direction);
		if (*t * denom > 0.0)
		{
			*t = *t / denom;
			if (*t >= 0.0)
				return (1);
		}
	}
	return (0);
}

int			sphere_intersect(t_object obj, t_ray ray, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = diff_num(ray.origin, obj.origin);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(oc, ray.direction);
	c = (oc.x * oc.x + oc.y * oc.y + oc.z * oc.z) - (obj.radius * obj.radius);
	disc = b * b - 4 * a * c;
	if (disc < 0.0)
		return (0);
	*t = (-b - sqrt(disc)) / (2 * a);
	if (*t < 0.0)
		*t = (-b + sqrt(disc)) / (2 * a);
	if (*t < 0.0)
		return (0);
	return (1);
}

int			intersect(t_ray ray, t_object obj, double *t)
{
	double	m;
	int		check;

	m = 0.0;
	check = 0;
	if (obj.type == 1)
		return (sphere_intersect(obj, ray, t));
	else if (obj.type == 3)
		return (cone_intersect(obj, ray, t));
	else if (obj.type == 2)
		return (cyl_intersect(obj, ray, t));
	else if (obj.type == 4)
		return (plane_intersect(obj, ray, t));
	return (0);
}
