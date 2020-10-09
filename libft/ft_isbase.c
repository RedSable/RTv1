/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isbase.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapricot <aapricot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:26:42 by aapricot          #+#    #+#             */
/*   Updated: 2020/08/07 21:15:46 by aapricot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isbase(int c, int base)
{
	if (ft_isdigit(c))
		return (c - '0' < base);
	if (ft_isalpha(c) && base > 10)
		return (c - 'a' + 10 < base);
	return (0);
}
