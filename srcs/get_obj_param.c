/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:35:33 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/15 17:39:29 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int				get_obj_type(char *str, int *type)
{
	if (!ft_strcmp(str, "sphere"))
		*type = 1;
	else if (!ft_strcmp(str, "cylinder"))
		*type = 2;
	else if (!ft_strcmp(str, "cone"))
		*type = 3;
	else if (!ft_strcmp(str, "plane"))
		*type = 4;
	else if (!ft_strcmp(str, "light"))
		*type = 5;
	else
		return (-1);
	return (1);
}

int				get_obj_color(char *str, int *color)
{
	int			r;
	int			g;
	int			b;
	int			i;

	i = 2;
	if (!ft_strcmp(str, "none"))
		return (1);
	if (str[0] == '0' && str[1] == 'x' && len_word(str) == 8)
	{
		while (str[i] != '\0')
		{
			if (ft_chartosix(str[i]) == -1)
				return (-1);
			i++;
		}
		r = 0xFF & (ft_chartosix(str[2]) * 16 + ft_chartosix(str[3]));
		g = 0xFF & (ft_chartosix(str[4]) * 16 + ft_chartosix(str[5]));
		b = 0xFF & (ft_chartosix(str[6]) * 16 + ft_chartosix(str[7]));
		*color = (r << 16) + (g << 8) + b;
		return (1);
	}
	return (-1);
}

int				get_obj_origin(char *str, t_vec3 *origin)
{
	char		**arr;
	int			i;

	i = 0;
	if (!ft_strcmp(str, "none"))
		return (1);
	arr = ft_strsplit(str, ',');
	while (i < 3)
	{
		if (len_word(arr[i]) > 10)
			return (-1);
		i++;
	}
	origin->x = get_double(arr[0]);
	origin->y = get_double(arr[1]);
	origin->z = get_double(arr[2]);
	free_tab(arr);
	return (1);
}

int				get_obj_direction(char *str, t_vec3 *direction)
{
	char		**arr;
	int			i;

	i = 0;
	if (!ft_strcmp(str, "none"))
	{
		return (1);
	}
	arr = ft_strsplit(str, ',');
	while (i < 3)
	{
		if (len_word(arr[i]) > 10)
			return (-1);
		i++;
	}
	direction->x = get_double(arr[0]);
	direction->y = get_double(arr[1]);
	direction->z = get_double(arr[2]);
	free_tab(arr);
	return (1);
}

int				get_obj_radius(char *str, double *radius)
{
	if (len_word(str) > 10)
		return (-1);
	if (!ft_strcmp(str, "none"))
		*radius = 0.0;
	else
		*radius = get_double(str);
	return (1);
}
