/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render2_0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:30:32 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/15 17:51:59 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vec3		gnah_sphere(t_vec3 hit_point, t_vec3 origin)
{
	t_vec3	res;

	res = diff_num(hit_point, origin);
	return (normalize(res));
}

t_vec3		get_normal_at_hit(t_object obj, t_vec3 hit_point,
								t_ray ray, double *t)
{
	t_vec3	res;
	double	m;
	double	k;

	obj.direction = normalize(obj.direction);
	if (obj.type == 1)
		return (gnah_sphere(hit_point, obj.origin));
	if (obj.type == 2)
	{
		m = dot_product(ray.direction, obj.direction) * *t
		+ dot_product(diff_num(ray.origin, obj.origin), obj.direction);
		res = diff_num(diff_num(hit_point, obj.origin),
		mult_num(m, obj.direction));
		return (normalize(res));
	}
	if (obj.type == 3)
	{
		m = dot_product(ray.direction, obj.direction) * *t
		+ dot_product(diff_num(ray.origin, obj.origin), obj.direction);
		k = tan(obj.radius / 2 * RAD);
		res = diff_num(diff_num(hit_point, obj.origin),
		mult_num(1 + k * k, mult_num(m, obj.direction)));
		return (normalize(res));
	}
	return (obj.direction);
}

t_ray		cast_camera_ray(t_camera camera, double x, double y)
{
	t_ray	ray;
	double	px;
	double	py;

	compute_uwv(&camera);
	px = (2 * ((x + 0.5) / WIDTH) - 1)
	* tan(camera.fov / 2 * PI / 180) * camera.imageaspectratio;
	py = (1 - 2 * ((y + 0.5) / HEIGHT)) * tan(camera.fov / 2 * PI / 180);
	ray.origin = camera.position;
	ray.direction = sum(mult_num(px, camera.u), mult_num(py, camera.v));
	ray.direction = diff_num(ray.direction, mult_num(1, camera.w));
	ray.direction = normalize(ray.direction);
	return (ray);
}

int			get_color(double nl, double x, int color)
{
	double	i;
	int		r;
	int		g;
	int		b;

	i = 1.0 * nl;
	r = clamp((int)(((color >> 16) & 0xFF) * i / x), 0, 255);
	g = clamp((int)(((color >> 8) & 0xFF) * i / x), 0, 255);
	b = clamp((int)(((color) & 0xFF) * i / x), 0, 255);
	if (nl > 0.0)
		return ((r << 16) | (g << 8) | b);
	return (0x000000);
}
