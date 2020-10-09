/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 16:04:24 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/18 20:15:11 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*lasts;
	char		*lastd;

	d = dst;
	s = src;
	if (!dst && !src && len > 0)
		return (0);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		lasts = (char *)s + (len - 1);
		lastd = (char *)d + (len - 1);
		while (len--)
			*lastd-- = *lasts--;
	}
	return ((void *)dst);
}
