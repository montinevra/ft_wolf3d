/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/17 16:52:17 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/04/17 16:52:17 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int argc, char const **argv)
{
	int		fd;
	t_wld	wld;




	if (argc != 2)
	{
		write(2, "usage:\t", 7);
		write(2, argv[0], ft_strlen(argv[0]));
		write(2, " mapname\n", 9);
	}
	else
	{
		if ((fd = open(argv[1], O_RDONLY)) < 0)
		{
			perror(argv[1]);
			exit(1);
		}
		wld = loadmap(fd);
		wld.name = (char *)argv[1];
		close(fd);
/*		debug
		int i = ~0, j = ~0;
		while (++j < wld.size.y)
		{
			i = ~0;
			while (wld.map[j][++i])
			{
				printf("%c", wld.map[j][i]);
			}
			printf("\n");
		}
		printf("world size = %d, %d\n", wld.size.x, wld.size.y);
//		*/

		wolf3d(wld);
		
	}
	return (0);
}
