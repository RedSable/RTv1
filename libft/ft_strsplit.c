/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 16:33:50 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/18 19:26:37 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char		**str;
	const char	*end;
	int			i;

	i = 0;
	if (!s || !(str = (char **)malloc((ft_wc(s, c) + 1) * sizeof(char *))))
		return (NULL);
	while (*s && *s == c)
		s++;
	while (*s)
	{
		end = s;
		while (*end && *end != c)
			end++;
		if (!(*(str + i++) = ft_strsub(s, 0, end - s)))
		{
			ft_matfree(str, i);
			return (NULL);
		}
		s = end;
		while (*s && *s == c)
			s++;
	}
	*(str + i) = NULL;
	return (str);
}
