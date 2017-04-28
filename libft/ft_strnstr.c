/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 13:33:29 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 13:34:57 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t llen;
	size_t i;
	size_t j;

	llen = ft_strlen(little);
	i = 0;
	if (llen)
	{
		while (big[i] && i < len)
		{
			j = 0;
			while (big[i + j] == little[j] && i + j < len)
			{
				if (j == llen - 1)
					return ((char *)(big + i));
				j++;
			}
			i++;
		}
		return (NULL);
	}
	return ((char *)big);
}
