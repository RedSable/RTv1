/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 11:29:32 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/15 02:30:26 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*pneedle;
	const char	*phaystack;
	int			ok;

	ok = 1;
	pneedle = needle;
	phaystack = haystack;
	while (*phaystack && *pneedle)
		ok &= *phaystack++ == *pneedle++;
	if (*pneedle)
		return (NULL);
	if (ok)
		return ((char *)(haystack));
	pneedle = needle;
	while (*haystack && *needle)
		if (*haystack++ == *needle)
			needle++;
		else
		{
			haystack -= needle - pneedle;
			needle = pneedle;
		}
	return (*(needle) ? NULL : (char *)(haystack - (needle - pneedle)));
}
