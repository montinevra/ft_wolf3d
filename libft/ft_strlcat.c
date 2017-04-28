/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 15:34:21 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/30 17:10:57 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	j;

	len_s = ft_strlen(src);
	if ((len_d = ft_strlen(dst)) > size)
		return (size + len_s);
	j = 0;
	while (src[j] && j + len_d + 1 < size)
	{
		dst[len_d + j] = src[j];
		j++;
	}
	dst[len_d + j] = '\0';
	return (len_d + len_s);
}
