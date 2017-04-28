/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 13:42:29 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 13:42:30 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
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
		ft_putchar_fd('-', fd);
		n *= -1;
	}
	else if (n == 0)
		ft_putchar_fd('0', fd);
	while (n)
	{
		number_array[index] = n % 10 + '0';
		n /= 10;
		index++;
	}
	while (index--)
		ft_putchar_fd(number_array[index], fd);
}
