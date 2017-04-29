/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/28 19:17:21 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/03/10 00:03:20 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
**	how to free properly:
**
**	char	*line;
**
**	while (get_next_line(fd, &line) > 0)
**	{
**		// whatever
**		free(line);
**	}
**	free(line);
*/

static t_stock	*new_stock(int fd)
{
	t_stock *stock;

	stock = (t_stock *)malloc(sizeof(t_stock));
	stock->fd = fd;
	stock->data = ft_strnew(BUFF_SIZE);
	stock->next = NULL;
	return (stock);
}

static t_stock	*get_curr_stock(t_stock *stock, int fd)
{
	if (stock->fd == fd)
		return (stock);
	else if (stock->next)
		return (get_curr_stock(stock->next, fd));
	return (stock->next = new_stock(fd));
}

static int		free_stock(int ret, t_stock **stock, int fd)
{
	t_stock	*curr_stock;
	t_stock	*prev_stock;

	curr_stock = get_curr_stock(*stock, fd);
	prev_stock = *stock;
	if (prev_stock != curr_stock)
	{
		while (prev_stock->next != curr_stock)
			prev_stock = prev_stock->next;
		if (curr_stock->next)
			prev_stock->next = curr_stock->next;
		else
			prev_stock->next = NULL;
	}
	else
	{
		if (curr_stock->next)
			*stock = curr_stock->next;
		else
			*stock = NULL;
	}
	ft_strdel(&(curr_stock->data));
	free(curr_stock);
	curr_stock = NULL;
	return (ret);
}

/*
**	concat and find newline
**	can read from buffer or stock
*/

static int		cat_nl(char **line, char *src, char *stock)
{
	char	*nl;

	*line = ft_strresize(*line, ft_strlen(*line) + ft_strlen(src));
	ft_strcat(*line, src);
	nl = ft_strchr(*line, '\n');
	if (nl && ft_strlen(nl))
	{
		*nl = '\0';
		ft_strcpy(stock, nl + 1);
		return (1);
	}
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static t_stock	*stock;
	t_stock			*curr_stock;
	char			*buffer;
	int				ret;

	if (!line || fd < 0)
		return (-1);
	*line = ft_strnew(0);
	if (!(stock))
		stock = new_stock(fd);
	curr_stock = get_curr_stock(stock, fd);
	if (cat_nl(line, curr_stock->data, curr_stock->data))
		return (1);
	ft_bzero(curr_stock->data, BUFF_SIZE);
	buffer = ft_strnew(BUFF_SIZE);
	while ((ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (cat_nl(line, buffer, curr_stock->data))
			break ;
	}
	ft_strdel(&buffer);
	if (ft_strlen(*line) || ret > 0)
		return (1);
	return (free_stock(ret, &stock, fd));
}
