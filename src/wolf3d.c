/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:22:17 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:22:20 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static t_pos	get_start(char **map)
{
	t_pos	start;
	int		i;
	int		j;

	j = ~0;
	while (map[++j])
	{
		i = ~0;
		while (map[j][++i])
		{
			if (map[j][i] == '2')
			{
				start.x = i + 0.5;
				start.y = j + 0.5;
				return (start);
			}
		}
	}
	start.x = 0.5;
	start.y = 0.5;
	return (start);
}

void			wolf3d(t_wld wld)
{
	t_mlx		mlx;

	mlx.wsize.x = 640 * 2;
	mlx.wsize.y = 400 * 2;
	wld.plr.pos = get_start(wld.map);
	wld.plr.rot = 0;
	wld.plr.vel.dir = 0;
	wld.plr.vel.mag = 0;
	wld.plr.fov.x = M_TAU / 4;
	wld.plr.fov.y = 2 * atan(tan(wld.plr.fov.x / 2) *
			mlx.wsize.y / mlx.wsize.x);
	mlx.data = &wld;
	mlx_driver(mlx);
	return ;
}
