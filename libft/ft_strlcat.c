/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 13:10:28 by aapricot          #+#    #+#             */
/*   Updated: 2019/09/08 15:49:11 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t slen;
	size_t dlen;

	slen = (size_t)ft_strlen(src);
	dlen = (size_t)ft_strnlen(dst, size);
	if (dlen == size)
		return (size + slen);
	if (slen < size - dlen)
		ft_strncpy(dst + dlen, src, slen + 1);
	else
	{
		ft_strncpy(dst + dlen, src, size - dlen - 1);
		*(dst + size - 1) = '\0';
	}
	return (dlen + slen);
}
