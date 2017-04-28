/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:04:21 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/16 16:21:12 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int nb;
	int i;
	int sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '0')
	{
		if (ft_tolower(str[i + 1]) == 'x')
			return (ft_atoi_base(&str[i + 2], 16));
		else
			return (ft_atoi_base(&str[i], 8));
	}
	else
	{
		if (str[i] == '-')
			sign = -1;
		if (str[i] == '+' || str[i] == '-')
			i++;
		nb = ft_atoi_base(&str[i], 10);
	}
	return (nb * sign);
}
