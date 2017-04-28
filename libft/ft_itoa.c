/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 13:27:23 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 15:02:48 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	'-' counts as a digit
*/

static unsigned int	get_digits(int n)
{
	unsigned int	digits;

	digits = 0;
	if (n < 0)
		digits++;
	if (n == 0)
		return (1);
	while (n)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

char				*ft_itoa(int n)
{
	char			*fresh;
	unsigned int	digits;

	digits = get_digits(n);
	if (!(fresh = (char *)malloc((digits) + 1)))
		return (NULL);
	if (n == 0)
		return (ft_strcpy(fresh, "0"));
	fresh[digits--] = '\0';
	if (n == -2147483648)
		return (ft_strcpy(fresh, "-2147483648"));
	if (n < 0)
	{
		fresh[0] = '-';
		n *= -1;
	}
	while (n)
	{
		fresh[digits--] = (n % 10) + '0';
		n /= 10;
	}
	return (fresh);
}
