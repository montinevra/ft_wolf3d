/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 23:31:03 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/30 20:50:45 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*fresh;

	if (!(fresh = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content || !content_size)
	{
		fresh->content = NULL;
		fresh->content_size = 0;
	}
	else
	{
		if (!(fresh->content = (void *)malloc(content_size)))
			return (NULL);
		fresh->content_size = content_size;
		ft_memcpy(fresh->content, content, content_size);
	}
	fresh->next = NULL;
	return (fresh);
}
