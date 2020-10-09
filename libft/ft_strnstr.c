/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 12:10:06 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/08 18:59:38 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *find, size_t len)
{
	const char *pfind = find;

	if (!*find)
		return ((char *)s);
	while (len-- && *s && *find)
		if (*s++ == *find)
			find++;
		else
		{
			s -= find - pfind;
			len += find - pfind;
			find = pfind;
		}
	return (*find ? NULL : (char *)(s - (find - pfind)));
}
