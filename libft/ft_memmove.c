/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 23:46:56 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 15:10:50 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	i = 0;
	if (src > dst)
		return (ft_memcpy(dst, src, len));
	while (i < len--)
		d[len] = s[len];
	return (dst);
}
