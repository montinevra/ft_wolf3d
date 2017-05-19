/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:23:20 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:39 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	1: left
**	2: right
**	3: middle/thumbs
**	4: scroll up
**	5: scroll down
*/

int	mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	t_plr	plr;

	plr = ((t_wld *)mlx->data)->plr;
	if (button == 4)
	{
		plr.fov.x *= .9;
		if (plr.fov.x < M_TAU / 180)
			plr.fov.x = M_TAU / 180;
		plr.fov.y = 2 * atan(tan(plr.fov.x / 2) * mlx->wsize.y / mlx->wsize.x);
	}
	if (button == 5)
	{
		plr.fov.x /= .9;
		if (plr.fov.x > M_TAU / 2.1)
			plr.fov.x = M_TAU / 2.1;
		plr.fov.y = 2 * atan(tan(plr.fov.x / 2) * mlx->wsize.y / mlx->wsize.x);
	}
	if (button == 3)
	{
		plr.fov.x = M_TAU / 4;
		plr.fov.y = 2 * atan(tan(plr.fov.x / 2) * mlx->wsize.y / mlx->wsize.x);
	}
	x = y;
	return (0);
}
