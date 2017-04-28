/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strresize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/04 11:19:35 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/12/04 16:41:48 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_strresize(char *ptr, size_t size)
{
	char	*newptr;
	size_t	len;

	newptr = ft_strnew(size);
	if (size < (len = ft_strlen(ptr)))
		ft_strncat(newptr, (const char *)ptr, size);
	else
		ft_strncat(newptr, (const char *)ptr, len);
	ft_strclr((char *)ptr);
	ft_strdel((char **)&ptr);
	return (newptr);
}
