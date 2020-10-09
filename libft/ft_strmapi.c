/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:39:26 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/15 01:52:23 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*p;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(p = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (*(s + i))
	{
		*(p + i) = f(i, *(s + i));
		i++;
	}
	*(p + i) = '\0';
	return (p);
}
