/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:01:09 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/14 18:23:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int len_word(char *str) 
{
	int len;
	
	len = 0;
	while(str[len] != '\0')
		len++;
	return (len);
}

int				ft_chartosix(char c)
{
	if (c == 'A')
		return (10);
	else if (c == 'B')
		return (11);
	else if (c == 'C')
		return (12);
	else if (c == 'D')
		return (13);
	else if (c == 'E')
		return (14);
	else if (c == 'F')
		return (15);
	else if (ft_isdigit(c))
		return (c - '0');
	else
		return (-1);
}

double			get_double(char *str) 
{
	char **arr;
	double res;
	int i;

	i = 0;
	res = 0.0;
	arr = ft_strsplit(str, '.');
	res += ft_atoi(arr[0]);
	res += ft_atoi(arr[1]) / pow(10, len_word(arr[1]));
	return (res);
}

int				get_obj_type(char *str, int *type)
{
	if (ft_strcmp(str, "sphere"))
		*type = 1;
	else if (ft_strcmp(str, "cylinder"))
		*type = 2;
	else if (ft_strcmp(str, "cone"))
		*type = 3;
	else if (ft_strcmp(str, "plane"))
		*type = 4;
	else if (ft_strcmp(str, "light"))
		*type = 5;
	else
		return (-1);
	return (1);
}

int				get_obj_color(char *str, int *color)
{
	int r;
	int g;
	int b;
	int i;

	i = 2;
	if (!ft_strcmp(str, "none"))
	{
		*color = 0;
		return (1);
	}
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
	char **arr;
	int		i;

	i = 0;
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
	return (1);
}

int				get_obj_direction(char *str, t_vec3 *direction)
{
	char **arr;
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
	return (1);
}


int			get_obj_radius(char *str, double *radius)
{
	if (len_word(str) > 10)
		return (-1);
	if (!ft_strcmp(str, "none"))
		*radius = 0.0;
	else
		*radius = get_double(str);
	return (1);
}

int				parse_str(t_object *obj, char *str)
{
	char		**word_array;
	int			i;

	i = 0;
	word_array = ft_strsplit(str, '\t');
	while (word_array[i] != NULL)
		i++;
	if (word_array == NULL || i != 5)
		return (-1);
	if (get_obj_type(word_array[0], &obj->type) == -1)
		return (-1);
	ft_putstr("type\n");
	if (get_obj_color(word_array[1], &obj->color) == -1)
		return (-1);
	ft_putstr("color\n");
	if (get_obj_origin(word_array[2], &obj->origin) == -1)
		return (-1);
	ft_putstr("origin\n");
	if (get_obj_direction(word_array[3], &obj->direction) == -1)
		return (-1);
	ft_putstr("direction\n");
	if (get_obj_radius(word_array[4], &obj->radius) == -1)
		return (-1);
	ft_putstr("radius\n");
	return (1);
}

int				parser(t_object *scene, int fd, int amount)
{
	char		*line;
	int			i;
	int			j;

	j = 0;
	while ((i = get_next_line(fd, &line) == 1))
	{
		i = parse_str(&scene[j], line);
		if (i < 1)
		{
			ft_putstr("parse_str\n");
			free(scene);
			free(line);
			return (-1);
		}
		scene[j].num = j;
		free(line);
		j++;
	}
	if (j < amount)
	{
		ft_putstr("j < amount\n");
		free(scene);
		return (-1);
	}
	return (1);
}

int			get_camera(char *str, t_camera *camera)
{
	char	**array;

	array = ft_strsplit(str, '\t');
	camera->fov = ft_atoi(array[1]);
	camera->imageAspectRatio = 1.0;
	camera->up = (t_vec3){.x = 0.0, .y = 1.0, .z = 0.0};
	if (get_obj_origin(array[2], &camera->position) == -1)
		return (-1);
	ft_putstr("its ok\n");
	if (get_obj_direction(array[3], &camera->direction) == -1)
		return (-1);
	ft_putstr("and this\n");
	return (1);
}