/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:31:57 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/13 19:33:02 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV_H
# define RTV_H
// # include "libft.h"
#include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "mlx.h"

# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6
# define KEY_ZERO 29
# define KEY_ONE 18
# define KEY_TWO 19
# define KEY_THREE 20
# define KEY_FOUR 21
# define KEY_FIVE 23
# define KEY_SIX 22
# define KEY_SEVEN 26
# define KEY_EIGHT 28
# define KEY_NINE 25
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
# define KEY_PLUS 24
# define KEY_MINUS 27
# define KEY_MULTI 67
# define KEY_SPACE 49
# define KEY_ENTER 36
# define KEY_ESC 53

# define WIDTH 800
# define HEIGHT 800
# define X_FACTOR (float)x_factor
# define Y_FACTOR (float)y_factor
# define PI 3.14159265359
# define RAD 0.01745329252
# define MAX_SOURCE_SIZE 0x100000

typedef struct s_object	t_object;
typedef struct s_vec3	t_vec3;
typedef struct s_param	t_param;
typedef struct s_image	t_image;
typedef struct s_camera	t_camera;
typedef struct s_ray	t_ray;

struct					s_image
{
	void				*img_ptr;
	char				*addr;
	int					bpp;
	int					size_line;
	int					endian;
};

struct					s_param
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_image				img;
	int					amount;
};

// struct					s_list
// {
// 	int					i;
// 	t_target			target;
// 	t_list				*next;
// };

struct					s_vec3
{
	double				x;
	double				y;
	double				z;
};

struct					s_ray
{
	t_vec3				origin;
	t_vec3				direction;
	double				mint;
	double				maxt;
};

struct					s_camera
{
	t_vec3				position;
	t_vec3				direction;
	t_vec3				w;
	t_vec3				u;
	t_vec3				v;
	t_vec3				up;
	double				fov;
	double				imageAspectRatio;
};

struct					s_object
{
	int					type;
	t_vec3				origin;
	t_vec3				direction;
	int					color;
	double				radius;
	int					num;
};

void		render(t_param *p, t_camera camera, t_object *scene);
double		dot_product(t_vec3 a, t_vec3 b);
t_vec3		sum(t_vec3 a, t_vec3 b);
t_vec3		diff_num(t_vec3 a, t_vec3 b);
t_vec3		mult_num(double num, t_vec3 b);
t_vec3		vector_multi(t_vec3 a, t_vec3 b);
t_vec3		normalize(t_vec3 direction);
int			intersect(t_ray ray, t_object obj, double *t);
t_vec3		vector_multi(t_vec3 a, t_vec3 b);
t_vec3		mult_num(double num, t_vec3 b);
t_vec3		diff_num(t_vec3 a, t_vec3 b);
t_vec3		sum(t_vec3 a, t_vec3 b);
double		dot_product(t_vec3 a, t_vec3 b);
int			clamp(int x, int min, int max);
void		compute_uwv(t_camera *camera);
t_vec3		normalize(t_vec3 direction);
double		light_lengh(t_vec3 a, t_vec3 b);

#endif