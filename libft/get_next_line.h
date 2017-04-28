/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 16:13:05 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/10 00:03:24 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1024
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_stock
{
	int				fd;
	char			*data;
	struct s_stock	*next;
}				t_stock;

int				get_next_line(const int fd, char **line);

#endif
