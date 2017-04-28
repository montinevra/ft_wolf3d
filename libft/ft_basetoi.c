/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basetoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/09 17:06:23 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/09 17:16:35 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_basetoi(const char *str, const char *base,
		const unsigned int radix)
{
	unsigned int	nb;
	size_t			i;

	i = 0;
	nb = 0;
	if (radix > 16)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	while (str[i] != '\0' && ft_strchr(base, str[i]) &&
			ft_strchr(base, str[i]) - base < radix)
	{
		nb *= radix;
		nb += ft_strchr(base, str[i]) - base;
		i++;
	}
	return (nb);
}
