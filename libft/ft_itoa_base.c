/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 22:21:57 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/01/11 21:48:50 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa_base(unsigned long n, const unsigned int radix)
{
	if (radix == 10)
		return (ft_itoa(n));
	return (ft_itobase(n, radix, "0123456789abcdefghijklmnopqrstuvwxyz"));
}
