/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:36:57 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 19:37:37 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

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

void			ft_error(int numerror)
{
	if (numerror == 1)
	{
		write(1, "KO\n", 3);
		exit(numerror);
	}
}

static int		init_params(t_param *p)
{
	if (!(p->mlx_ptr = mlx_init()))
		return (-1);
	if (!(p->win_ptr = mlx_new_window(p->mlx_ptr, WIDTH, HEIGHT, "RTv1")))
		return (-1);
	p->img.img_ptr = mlx_new_image(p->mlx_ptr, WIDTH, HEIGHT);
	p->img.addr = mlx_get_data_addr(p->img.img_ptr, &p->img.bpp, &p->img.size_line, &p->img.endian);
	return (0);
}

int				main(int ac, char **av)
{
	// int			fd;
	t_param		p;
	t_object	*scene;
	t_camera	camera;

	if (ac != 2)
		ft_error(1);
	if (init_params(&p) == -1)
		ft_error(1);
	if (av[0][0] != 'a') //заглушка для Wall Wextra Werror
		;
	scene = (t_object *)malloc(sizeof(t_object) * 5);
	//sphere
	scene[0].color = 0xFF0000;
	scene[0].direction = (t_vec3){.x = 0.0, .y = 0.0, .z = 0.0};
	scene[0].origin = (t_vec3){.x = 0.0, .y = -1.0, .z = 7.0};
	scene[0].type = 1;
	scene[0].radius = 1.0;
	scene[0].num = 0;

	//cone
	scene[1].color = 0x00FF00;
	scene[1].direction = (t_vec3){.x = -0.3, .y = 1.0, .z = 0.0};
	scene[1].origin = (t_vec3){.x = 1.0, .y = -1.0, .z = 5.0};
	scene[1].type = 3;
	scene[1].radius = 30.0;
	scene[1].num = 1;

	//cylinder
	scene[2].color = 0x0000FF;
	scene[2].direction = (t_vec3){.x = 0.6, .y = 1.0, .z = 1.5};
	scene[2].origin = (t_vec3){.x = 1.0, .y = 3.0, .z = 7.0};
	scene[2].type = 2;
	scene[2].radius = 0.4;
	scene[2].num = 2;

	//plane
	scene[4].color = 0xEAFF00;
	scene[4].direction = (t_vec3){.x = 0.0, .y = 1.0, .z = 0.0};
	scene[4].origin = (t_vec3){.x = 0.0, .y = -2.0, .z = 3.0};
	scene[4].type = 4;
	scene[4].radius = 1.0;
	scene[4].num = 3;

	// scene[2].color = 0x0000FF;
	// scene[2].direction = (t_vec3){.x = 0.0, .y = 0.0, .z = 0.0};
	scene[3].origin = (t_vec3){.x = 4.0, .y = 10.0, .z = -2.0};
	scene[3].type = 5;
	// scene[2].radius = 1.0;
	p.amount = 5;
	camera.fov = 90;
	camera.position = (t_vec3){.x = 4.0, .y = 0.0, .z = 0.0};
	camera.direction = (t_vec3){.x = -2.0, .y = 0.0, .z = 1.0};
	camera.imageAspectRatio = 1.0;
	camera.up = (t_vec3){.x = 0.0, .y = 1.0, .z = 0.0};
	// init_params(&p); 
	// memset(p.img.addr, 0x000000, WIDTH * HEIGHT);
	render(&p, camera, scene);
	mlx_hook(p.win_ptr, 2, 0, key_event, &p);
	// mlx_hook(p->win_ptr, 2, 0, key_event, p);
	// mlx_hook(p->win_ptr, 4, 0, mouse_press, p);
	// mlx_hook(p->win_ptr, 6, 0, mouse_move, p);
	mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, p.img.img_ptr, 0, 0);
	// if ((fd = open(av[1], O_RDONLY)) < 0)
	// 	ft_error(1);
	// if (((fd = pars_file(&list))))
	mlx_loop(p.mlx_ptr);
	return (0);
}