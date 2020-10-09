/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:33:44 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/15 02:30:04 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char *p;
	char *rp;

	if (!s || !f)
		return (NULL);
	if (!(p = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	rp = p;
	while (*s)
	{
		*p++ = f(*s);
		s++;
	}
	*p = '\0';
	return (rp);
}
