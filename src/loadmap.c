/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:40:05 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:40:06 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_coord	get_size(int fd, char **line)
{
	t_coord	size;

	if (get_next_line(fd, line) > 0)
	{
		size.x = ft_atoi(*line);
		size.y = ft_atoi(ft_strchr(*line, ' '));
		free(*line);
	}
	else
	{
		write(2, "Invalid map\n", 12);
		exit(1);
	}
	if (!size.x || !size.y)
	{
		write(2, "Invalid map\n", 12);
		exit(1);
	}
	return (size);
}

t_wld			loadmap(int fd)
{
	t_wld	wld;
	char	*line;
	int		i;

	wld.size = get_size(fd, &line);
	wld.map = (char **)malloc(sizeof(char *) * (wld.size.y));
	i = ~0;
	while (get_next_line(fd, &line) > 0 && ++i < wld.size.y)
	{
		wld.map[i] = ft_strndup(line, wld.size.x);
		free(line);
	}
	free(line);
	return (wld);
}
