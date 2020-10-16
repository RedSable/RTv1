/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 18:01:09 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/15 18:20:14 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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
	if (get_obj_color(word_array[1], &obj->color) == -1)
		return (-1);
	if (get_obj_origin(word_array[2], &obj->origin) == -1)
		return (-1);
	if (get_obj_direction(word_array[3], &obj->direction) == -1)
		return (-1);
	if (get_obj_radius(word_array[4], &obj->radius) == -1)
		return (-1);
	free_tab(word_array);
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
		if (j >= amount)
			return (-1);
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
		return (-1);
	return (1);
}

int				get_camera(char *str, t_camera *camera)
{
	char		**array;

	array = ft_strsplit(str, '\t');
	camera->fov = ft_atoi(array[1]);
	camera->imageaspectratio = 1.0;
	camera->up = (t_vec3){.x = 0.0, .y = 1.0, .z = 0.0};
	if (get_obj_origin(array[2], &camera->position) == -1)
		return (-1);
	if (get_obj_direction(array[3], &camera->direction) == -1)
		return (-1);
	free_tab(array);
	return (1);
}
