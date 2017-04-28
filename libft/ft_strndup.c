/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:34:07 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/10/01 23:25:15 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*copy;

	if (!(copy = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	ft_strncpy(copy, s1, n);
	copy[n] = '\0';
	return (copy);
}
