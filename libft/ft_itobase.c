/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itobase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 15:08:30 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/01/11 23:10:57 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	get_digits_base(unsigned long n, const unsigned int radix)
{
	unsigned int	digits;

	digits = 0;
	if (n == 0)
		return (1);
	if (radix <= 1)
		return (1);
	while (n)
	{
		digits++;
		n /= radix;
	}
	return (digits);
}

/*
**	radix is the number of unique digits;
**	base is an array representing said digits
*/

char				*ft_itobase(unsigned long n, const unsigned int radix,
		const char *base)
{
	char			*fresh;
	unsigned int	digits;

	digits = get_digits_base(n, radix);
	if (!(fresh = ft_strnew(digits)))
		return (NULL);
	if (n == 0)
		fresh[0] = '0';
	else
	{
		if (radix < 2 || radix > ft_strlen(base))
			return ("undefined");
		while (n)
		{
			fresh[--digits] = base[(n % radix)];
			n /= radix;
		}
	}
	return (fresh);
}
