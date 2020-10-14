/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:32:00 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 19:32:34 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double		light_lengh(t_vec3 a, t_vec3 b)
{
	double	k;
	double	l;
	double	m;
	double	res;

	k = pow(b.x - a.x, 2);
	l = pow(b.y - a.y, 2);
	m = pow(b.z - a.z, 2);
	res = sqrt(k + l + m);
	return (fabs(res));
}

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

void		compute_uwv(t_camera *camera)
{
	camera->w.x = -camera->direction.x;
	camera->w.y = -camera->direction.y;
	camera->w.z = -camera->direction.z;
	camera->w = normalize(camera->w);
	camera->u = vector_multi(camera->up, camera->w);
	camera->u.x = -camera->u.x;
	camera->u.y = -camera->u.y;
	camera->u.z = -camera->u.z;
	camera->v = vector_multi(camera->w, camera->u);
	camera->v.x = -camera->v.x;
	camera->v.y = -camera->v.y;
	camera->v.z = -camera->v.z;
}

int			clamp(int x, int min, int max)
{
	if (x < min)
		x = min;
	if (x > max)
		x = max;
	return (x);
}
