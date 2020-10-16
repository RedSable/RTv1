/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:36:57 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/15 17:47:34 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static void		die(const char *message, int numerror)
{
	if (!message)
	{
		ft_putendl_fd("Invalid file.", 2);
		exit(numerror);
	}
	if (ft_strcmp("", message) == 0)
		exit(numerror);
	ft_putendl_fd(message, 2);
	exit(numerror);
}

int				key_event(int keycode, t_param *p)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(p->mlx_ptr, p->img.img_ptr);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		exit(0);
	}
	return (0);
}

static int		init_params(t_param *p)
{
	if (!(p->mlx_ptr = mlx_init()))
		return (-1);
	if (!(p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "RTv1")))
		return (-1);
	p->img.img_ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT);
	p->img.addr = mlx_get_data_addr(p->img.img_ptr, &p->img.bpp,
	&p->img.size_line, &p->img.endian);
	return (0);
}

void			second_main(int fd, int amount,
				t_camera *camera, t_object *scene)
{
	char		*line;

	get_next_line(fd, &line);
	if (get_camera(line, camera) == -1)
		die(NULL, -4);
	free(line);
	if (((fd = parser(scene, fd, amount)) == -1))
		die(NULL, -4);
	close(fd);
}

int				main(int ac, char **av)
{
	int			fd;
	t_param		p;
	t_object	*scene;
	t_camera	camera;
	char		*line;

	if (ac != 2)
		die("Bad arguments", -2);
	if ((fd = open(av[1], O_RDONLY)) <= 0)
		die("No such file.", -2);
	if (init_params(&p) == -1)
		die("Error", -2);
	if (get_next_line(fd, &line) < 0)
		die("It's directory", -2);
	p.amount = ft_atoi(line);
	free(line);
	scene = (t_object *)malloc(sizeof(t_object) * p.amount);
	second_main(fd, p.amount, &camera, scene);
	render(&p, camera, scene);
	mlx_hook(p.win_ptr, 2, 0, key_event, &p);
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.img_ptr, 0, 0);
	mlx_loop(p.mlx_ptr);
	return (0);
}
