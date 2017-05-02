#include "wolf3d.h"

static t_coord	get_size(int fd, char **line)
{
	t_coord	size;

	if (get_next_line(fd, line) > 0)
	{
		// printf("................got first line\n");									////debug
		size.x = ft_atoi(*line);
		size.y = ft_atoi(ft_strchr(*line, ' '));
		// printf("................size = %d, %d\n", size.x, size.y);													//debug
		// printf("................freeing first line\n");														//debug
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

t_wld		loadmap(int fd)
{
	t_wld	wld;
	// t_coord	size;
	char	*line;
	int 	i;

	// printf("................mallocing line\n");															///debug
	// line = (char **)malloc(sizeof(char *));
	// printf("................mallocied\n");															///debug
	wld.size = get_size(fd, &line);
	wld.map = (char **)malloc(sizeof(char *) * (wld.size.y));
	i = ~0;
	while (get_next_line(fd, &line) > 0 && ++i < wld.size.y)
	{
		wld.map[i] = ft_strndup(line, wld.size.x);
		free(line);
	}
	// printf("lines = =%d\n", i);														//debug
	// wld.map[i] = NULL;
	free(line);
	// free(line);

	return (wld);
}