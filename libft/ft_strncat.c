/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:13:25 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/08 15:49:28 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*pd;
	char	*ps;
	size_t	l;

	pd = s1;
	s1 += ft_strlen(s1);
	ps = (char *)s2;
	l = 0;
	while (*(ps + l))
	{
		if (l == n)
			break ;
		l++;
	}
	*(s1 + l) = '\0';
	ft_memcpy(s1, s2, l);
	return (pd);
}
