/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:39:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/09 20:50:07 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double		dot_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3		sum(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

t_vec3		diff_num(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_vec3		mult_num(double num, t_vec3 b)
{
	t_vec3	res;

	res.x = num * b.x;
	res.y = num * b.y;
	res.z = num * b.z;
	return (res);
}

// t_vec3		vector_matrix_multi(t_vec3 origin, double *camera_to_world)
// {
// 	;
// }

t_vec3		normalize(t_vec3 direction)
{
	double	x;
	double	y;
	double	z;

	x = direction.x;
	y = direction.y;
	z = direction.z;
	direction.x = x / (sqrt((x * x) + (y * y) + (z * z)));
	direction.y = y / (sqrt((x * x) + (y * y) + (z * z)));
	direction.z = z / (sqrt((x * x) + (y * y) + (z * z)));
	return (direction);
}

// double		*set_camera_matrix(t_camera camera)
// {
// 	double	*m;

// 	m = get_rotation_matrix(camera.rotate.x, camera.rotate.y, camera.rotate.z);
// 	m[3] = camera.position.x;
// 	m[7] = camera.position.y;
// 	m[11] = camera.position.z;
// 	return (m);
// }

t_vec3		get_normal_at_hit(t_object obj, t_vec3 hit_point, t_ray ray, double *t)
{
	t_vec3	res;
	double	m;

	m = 0.0;
	if (obj.type == 1)
	{
		res = diff_num(hit_point, obj.origin);
		return (normalize(res));
	}
	if (obj.type == 3)
	{
		m = dot_product(ray.direction, obj.direction) * *t + dot_product(diff_num(ray.origin, obj.origin), obj.direction);
		res = diff_num(diff_num(hit_point, obj.origin),mult_num(m, obj.direction));
		return (normalize(res));
	}
	return (normalize(obj.direction));
}

t_ray		cast_camera_ray(t_camera camera, double x, double y)
{
	t_ray	ray;
	double	px;
	double	py;
	double	*camera_to_world;

	px = (2 * ((x + 0.5) / WIDTH) - 1) * tan(camera.fov / 2 * M_PI / 180) * camera.imageAspectRatio;
	py = (1 - 2 * ((y + 0.5) / HEIGHT)) * tan(camera.fov / 2 * M_PI / 180);
	ray.origin = (t_vec3){.x = 0.0, .y = 0.0, .z = 0.0};
	ray.direction = (t_vec3){.x = px, .y = py, .z = 1.0};
	// camera_to_world = set_camera_matrix(camera);
	// ray.origin = vector_matrix_multi(ray.origin, camera_to_world);
	// ray.direction = vector_matrix_multi(ray.direction, camera_to_world);
	ray.direction = diff_num(ray.direction, ray.origin);
	ray.direction = normalize(ray.direction);
	return (ray);
}

// int			plane_intersect(t_object obj, t_ray ray, double *t)
// {
// 	t_vec3	oc;
// 	double	x_v;
// 	double	d_v;

// 	*t = 0.0;
// 	oc = diff_num(ray.origin, obj.origin);
// 	obj.direction = normalize(obj.direction);
// 	x_v = dot_product(oc, obj.direction);
// 	d_v = dot_product(ray.direction, obj.direction);
// 	if (dot_product(ray.direction, obj.direction) == 0)
// 		return (0);
// 	if ((x_v > 0 && d_v < 0) || (x_v < 0 && d_v > 0))
// 	{
// 		*t = -(dot_product(oc, obj.direction) / dot_product(ray.direction, obj.direction));
// 		return (1);
// 	}
// 	// *t = -(dot_product(oc, obj.direction) / dot_product(ray.direction, obj.direction));
// 	// return (1);
// 	return (0);
// }

int			cyl_intersect(t_object obj, t_ray ray, double *t)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = diff_num(ray.origin, obj.origin);
	a = dot_product(ray.direction, ray.direction) - pow(dot_product(ray.direction, obj.direction), 2);
	b = 2 * (dot_product(ray.direction, oc) - dot_product(ray.direction, obj.direction) * dot_product(oc, obj.direction));
	c = dot_product(oc, oc) - pow(dot_product(oc, obj.direction), 2) - obj.radius * obj.radius;
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

	// obj.direction = normalize(obj.direction);
	denom = dot_product(ray.direction, obj.direction);
	if(denom != 0.0)
	{
		a = diff_num(obj.origin, ray.origin);
		// a = normalize(a);
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
	// b = 2 * (oc.x * ray.direction.x + oc.y * ray.direction.y + oc.z * ray.direction.z);
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
	if (obj.type == 3)
		return (cyl_intersect(obj, ray, t));
	if (obj.type == 4)
		return (plane_intersect(obj, ray, t));
	return (0);
}

int			clamp(int x, int min, int max)
{
	if (x < min)
		x = min;
	if (x > max)
		x = max;
	return (x);
}

int			shade(t_object *scene, t_object obj, t_vec3 hit_point, t_vec3 normal, t_param *p)
{
	t_vec3	light;
	t_ray	ray;
	double	nl;
	double	i;
	double	foo;
	double	x;
	int		j;
	int		r;
	int		g;
	int		b;

	i = 0.0;
	j = 0;
	x = 1.0;
	light = diff_num(scene[3].origin, hit_point);
	light = normalize(light);
	ray.direction = light;
	// ray.origin = sum(hit_point, (t_vec3){.x = 0.001, .y = 0.001, .z = -0.1});
	ray.origin = hit_point;
	nl = normal.x * light.x + normal.y * light.y + normal.z * light.z;
	while (j < p->amount)
	{
		if (obj.num == scene[j].num)
		{
			j++;
			continue;
		}
		if ((intersect(ray, scene[j], &foo) == 1) && foo > 0)
		{
			x = 5.0;
			break ;
		}
		j++;
	}
	if (nl > 0.0)
	{
		i = 1.0 * nl;// / (sqrt(pow(normal.x, 2) + pow(normal.y, 2) + pow(normal.z, 2)) * sqrt(pow(light.x, 2) + pow(light.y, 2) + pow(light.z, 2)));
		r = clamp((int)(((obj.color >> 16) & 0xFF) * i / x), 0, 255);
		g = clamp((int)(((obj.color >> 8) & 0xFF) * i / x), 0, 255);
		b = clamp((int)(((obj.color) & 0xFF) * i / x), 0, 255);
		return ((r << 16) | (g << 8) | b);
	}
	return (0x000000);
}

int			trace_ray(t_ray ray, t_object *scene, t_param *p)
{
	double	t;
	int		i;
	t_vec3	hit_point;
	t_vec3	normal;
	int		color;

	i = 0;
	t = 1;
	while (i < p->amount)
	{
		if (intersect(ray, scene[i], &t) != 0)
		{
			ray.mint = t;
			hit_point = sum(ray.origin, mult_num(t, ray.direction));
			normal = get_normal_at_hit(scene[i], hit_point, ray, &t);
			color = shade(scene, scene[i], hit_point, normal, p);
			// color = scene[i].color;
			return (color);
		}
		else
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
		while(x < WIDTH)
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