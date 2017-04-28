/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 13:18:41 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/10/01 23:31:13 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t');
}

char		*ft_strtrim(char const *s)
{
	char	*fresh;
	size_t	start;
	size_t	end;
	size_t	i;

	if (!s)
		return (NULL);
	start = 0;
	end = ft_strlen(s);
	while (s[start] && is_whitespace(s[start]))
		start++;
	while (is_whitespace(s[end - 1]) && end >= start)
		end--;
	if (end <= start)
		end = start + 1;
	if (!(fresh = (char *)malloc(sizeof(char) * (end - start + 1))))
		return (NULL);
	i = -1;
	while (start + ++i < end)
		fresh[i] = s[start + i];
	fresh[i] = '\0';
	return (fresh);
}
