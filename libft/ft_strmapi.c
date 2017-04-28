/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 02:39:17 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 02:39:26 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*fresh;
	size_t	len;
	int		i;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!(fresh = (char *)malloc(len + 1)))
		return (NULL);
	i = 0;
	while (s[i])
	{
		fresh[i] = f(i, *(char *)(s + i));
		i++;
	}
	fresh[i] = 0;
	return (fresh);
}
