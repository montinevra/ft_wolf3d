/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 15:07:36 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 15:07:37 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	int len;
	int i;
	int j;

	len = ft_strlen(little);
	i = 0;
	if (len)
	{
		while (big[i])
		{
			j = 0;
			while (big[i + j] == little[j])
			{
				if (j == len - 1)
					return ((char *)(big + i));
				j++;
			}
			i++;
		}
		return (NULL);
	}
	return ((char *)big);
}
