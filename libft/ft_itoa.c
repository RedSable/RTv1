/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 02:45:42 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/15 02:45:45 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		sign;
	char	*p;
	int		size;
	int		tmp;

	size = 1;
	sign = n < 0 ? 1 : 0;
	tmp = n;
	while (tmp /= 10)
		size++;
	if (!(p = (char *)malloc(size + sign + 1)))
		return (NULL);
	*(p + size + sign) = '\0';
	if (sign)
		*p++ = '-';
	while (size--)
	{
		*(p + size) = (((n % 10) < 0) ? -(n % 10) : (n % 10)) + '0';
		n /= 10;
	}
	return (p - sign);
}
