/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 13:36:48 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 13:36:50 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	char	number_array[11];
	int		index;

	index = 0;
	if (n == -2147483648)
	{
		number_array[index] = 8 + '0';
		n /= 10;
		index++;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n *= -1;
	}
	else if (n == 0)
		ft_putchar('0');
	while (n)
	{
		number_array[index] = n % 10 + '0';
		n /= 10;
		index++;
	}
	while (index--)
		ft_putchar(number_array[index]);
}
