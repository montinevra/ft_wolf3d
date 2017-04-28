/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 23:32:34 by pvan-erp          #+#    #+#             */
/*   Updated: 2016/09/28 23:33:06 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *fresh;
	t_list *curr;

	if (!(fresh = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	curr = fresh;
	while (lst)
	{
		*curr = *f(lst);
		curr->next = (t_list *)malloc(sizeof(t_list));
		curr = curr->next;
		lst = lst->next;
	}
	return (fresh);
}
