/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:29:04 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 19:29:27 by aapricot         ###   ########.fr       */
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

t_vec3		vector_multi(t_vec3 a, t_vec3 b)
{
	t_vec3	res;

	res = (t_vec3){.x = a.y * b.z - a.z * b.y,
	.y = a.z * b.x - a.x * b.z, .z = a.x * b.y - a.y * b.x};
	return (res);
}
