/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 19:39:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/15 17:39:12 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vec3			get_light(t_object *scene, t_vec3 hit_point, int *j)
{
	t_vec3		light;

	*j = 0;
	while (scene[*j].type != 5)
		*j += 1;
	light = diff_num(scene[*j].origin, hit_point);
	light = normalize(light);
	return (light);
}

double			get_nl(t_vec3 normal, t_ray ray)
{
	return (normal.x * ray.direction.x + normal.y
			* ray.direction.y + normal.z * ray.direction.z);
}

int				shade(t_object *scene, t_object obj, t_vec3 hit_point,
					t_vec3 normal)
{
	t_ray		ray;
	t_vec3		obj_hit;
	t_vec3		garbage;
	double		foo;
	int			j;

	ray.direction = get_light(scene, hit_point, &j);
	ray.origin = hit_point;
	garbage = (t_vec3){.x = 1.0, .y = light_lengh(hit_point, scene[j].origin)};
	garbage.z = get_nl(normal, ray);
	j = -1;
	while (++j < obj.amount)
	{
		if (obj.num == scene[j].num)
			j++;
		else if ((intersect(ray, scene[j], &foo) == 1) && (foo > 0))
		{
			obj_hit = sum(ray.origin, mult_num(foo, ray.direction));
			if (light_lengh(obj_hit, hit_point) > garbage.y)
				j++;
			else if ((garbage.x = 5.0) != 0.0)
				break ;
		}
	}
	return (get_color(garbage.z, garbage.x, obj.color));
}

int				trace_ray(t_ray ray, t_object *scene, t_param *p)
{
	t_vec3		garbage;
	int			color;
	t_vec3		hit_point;
	t_vec3		normal;
	t_object	obj;

	garbage = (t_vec3){.x = 1.0, .y = 1000.0, .z = 0.0};
	while ((int)garbage.z < (obj.amount = p->amount))
	{
		if (intersect(ray, scene[(int)garbage.z], &garbage.x) != 0)
		{
			if (garbage.x < garbage.y)
			{
				garbage.y = garbage.x;
				obj = scene[(int)garbage.z];
				continue;
			}
		}
		hit_point = sum(ray.origin, mult_num(garbage.y, ray.direction));
		normal = get_normal_at_hit(obj, hit_point, ray, &garbage.y);
		color = shade(scene, obj, hit_point, normal);
		garbage.y == 1000.0 ? color = 0x646464 : 0;
		garbage.z += 1;
	}
	return (color);
}

void			render(t_param *p, t_camera camera, t_object *scene)
{
	t_ray		ray;
	int			color;
	int			x;
	int			y;

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
