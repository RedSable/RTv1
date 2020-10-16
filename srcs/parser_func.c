/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:33:11 by aapricot          #+#    #+#             */
/*   Updated: 2020/10/15 17:48:23 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void		free_tab(char **tab)
{
	int		n;

	n = 0;
	while (NULL != tab[n])
	{
		free(tab[n]);
		tab[n] = NULL;
		n += 1;
	}
	free(tab);
}

int			len_word(char *str)
{
	int len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

int			ft_chartosix(char c)
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

double		get_double(char *str)
{
	char	**arr;
	double	res;
	int		i;
	int		k;

	i = 1;
	res = 0.0;
	arr = ft_strsplit(str, '.');
	if (arr[0][0] == '-' && arr[0][1] == '0')
		i = -1;
	k = ft_atoi(arr[1]);
	res += ft_atoi(arr[0]);
	res += (double)(k / pow(10, len_word(arr[1])));
	res *= i;
	free_tab(arr);
	return (res);
}
