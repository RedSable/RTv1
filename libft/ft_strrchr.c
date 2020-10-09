/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:20:50 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/15 02:30:21 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char *p;
	const char *rp;

	if (c == '\0')
		return (ft_strchr(s, '\0'));
	rp = NULL;
	while ((p = ft_strchr(s, c)) != NULL)
	{
		rp = p;
		s = p + 1;
	}
	return ((char *)rp);
}
