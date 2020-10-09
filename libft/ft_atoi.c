/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 11:16:13 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/18 20:39:26 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long int		res;
	int					sign;

	sign = 1;
	res = 0;
	while (ft_isspace((int)*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = *str++ == '-' ? -1 : 1;
	while (*str != '\0' && *str >= 48 && *str <= 57)
	{
		if ((res * 10) < res)
			return ((sign == -1) ? 0 : -1);
		res = res * 10 + (*str++ - '0');
	}
	return (res * sign);
}
