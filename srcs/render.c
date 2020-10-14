/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:39:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 21:00:32 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vec3		get_normal_at_hit(t_object obj, t_vec3 hit_point,
								t_ray ray, double *t)
{
	t_vec3	res;
	double	m;
	double	k;

	m = 0.0;
	obj.direction = normalize(obj.direction);
	if (obj.type == 1)
	{
		res = diff_num(hit_point, obj.origin);
		return (normalize(res));
	}
	if (obj.type == 2)
	{
		m = dot_product(ray.direction, obj.direction) * *t + dot_product(diff_num(ray.origin, obj.origin), obj.direction);
		res = diff_num(diff_num(hit_point, obj.origin), mult_num(m, obj.direction));
		return (normalize(res));
	}
	if (obj.type == 3)
	{
		m = dot_product(ray.direction, obj.direction) * *t + dot_product(diff_num(ray.origin, obj.origin), obj.direction);
		k = tan(obj.radius / 2 * RAD);
		res = diff_num(diff_num(hit_point, obj.origin), mult_num(1 + k * k, mult_num(m, obj.direction)));
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
	px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(camera.fov / 2 * PI / 180) * camera.imageAspectRatio;
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
	return ((r << 16) | (g << 8) | b);
}

int			shade(t_object *scene, t_object obj, t_vec3 hit_point, t_vec3 normal, t_param *p)
{
	t_vec3	light;
	t_ray	ray;
	t_vec3	obj_hit;
	double	nl;
	double	foo;
	double	x;
	double	lengh;
	int		j;

	j = 0;
	x = 1.0;
	while (scene[j].type != 5)
		j++;
	lengh = light_lengh(hit_point, scene[j].origin);
	light = diff_num(scene[j].origin, hit_point);
	light = normalize(light);
	ray.direction = light;
	ray.origin = hit_point;
	nl = normal.x * light.x + normal.y * light.y + normal.z * light.z;
	j = 0;
	while (j < p->amount)
	{
		if (obj.num == scene[j].num)
		{
			j++;
			continue;
		}
		if ((intersect(ray, scene[j], &foo) == 1) && (foo > 0))
		{
			obj_hit = sum(ray.origin, mult_num(foo, ray.direction));
			if (light_lengh(obj_hit, hit_point) > lengh)
			{
				j++;
				continue;
			}
			x = 5.0;
			break ;
		}
		j++;
	}
	if (nl > 0.0)
		return (get_color(nl, x, obj.color));
	return (0x000000);
}

int			trace_ray(t_ray ray, t_object *scene, t_param *p)
{
	double	t;
	int		i;
	t_vec3	hit_point;
	t_vec3	normal;
	int		color;
	double	mint;
	t_object	obj;

	mint = 1000.0;
	i = 0;
	t = 1;
	while (i < p->amount)
	{
		if (intersect(ray, scene[i], &t) != 0)
		{
			if (t < mint)
			{
				mint = t;
				obj = scene[i];
				continue;
			}
		}
		hit_point = sum(ray.origin, mult_num(mint, ray.direction));
		normal = get_normal_at_hit(obj, hit_point, ray, &mint);
		color = shade(scene, obj, hit_point, normal, p);
		if (mint == 1000.0)
			color = 0x646464;
		i++;
	}
	return (color);
}

void		render(t_param *p, t_camera camera, t_object *scene)
{
	t_ray	ray;
	int		color;
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			ray = cast_camera_ray(camera, x, y);
			color = trace_ray(ray, scene, p);
			((int *)p->img.addr)[y * WIDTH + x] = color;
			x++;
		}
		x = 0;
		y++;
	}
}
