/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ustrlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 00:25:02 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/02/06 01:10:37 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ustrlen(const wchar_t *s)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] >= 0x4000000)
			len += 6;
		else if (s[i] >= 0x200000)
			len += 5;
		else if (s[i] >= 0x10000)
			len += 4;
		else if (s[i] >= 0x800)
			len += 3;
		else if (s[i] >= 0x80)
			len += 2;
		else
			len += 1;
		i++;
	}
	return (len);
}
