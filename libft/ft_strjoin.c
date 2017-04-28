/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 02:40:26 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 02:40:29 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*fresh;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(fresh = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		fresh[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		fresh[i + j] = s2[j];
		j++;
	}
	fresh[i + j] = 0;
	return (fresh);
}
