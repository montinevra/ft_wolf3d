/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/01 14:33:05 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/10/01 14:33:06 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	identical to ft_isdigit(). library version accounts for locale
*/

int	ft_isnumber(int c)
{
	return (c >= '0' && c <= '9');
}
