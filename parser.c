/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:01:09 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 18:56:26 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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
	return (1);
}

int				get_obj_origin(char *str, t_vec3 *origin)
{
	return (1);
}

int				get_obj_direction(char *str, t_vec3 *direction)
{
	return (1);
}

int				get_obj_radius(char *str, double *radius)
{
	return (1);
}

int				parse_str(t_object *obj, char *str)
{
	char		**word_array;

	word_array = ft_strsplit(str, '\t');
	if (word_array == NULL || sizeof(word_array) != 5)
		return (-1);
	if (get_obj_type(word_array[0], obj->type) == -1)
		return (-1);
	get_obj_color(word_array[1], obj->color);
	get_obj_origin(word_array[2], &obj->origin);
	get_obj_directio(word_array[3], &obj->direction);
	get_obj_radius(word_array[4], &obj->radius);
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
		free(scene);
		return (-1);
	}
	return (1);
}