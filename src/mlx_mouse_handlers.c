/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_mouse_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:23:20 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/08 21:25:24 by pvan-erp         ###   ########.fr       */
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
	t_wld	*wld;

	wld = (t_wld *)mlx->data;
	if (button == 4)
	{
		wld->plr.fov.x *= .9;
		if (wld->plr.fov.x < M_TAU / 180)
			wld->plr.fov.x = M_TAU / 180;
		wld->plr.fov.y = 2 * atan(tan(wld->plr.fov.x / 2) *
				mlx->wsize.y / mlx->wsize.x);
	}
	if (button == 5)
	{
		wld->plr.fov.x /= .9;
		if (wld->plr.fov.x > M_TAU / 2.1)
			wld->plr.fov.x = M_TAU / 2.1;
		wld->plr.fov.y = 2 * atan(tan(wld->plr.fov.x / 2) *
				mlx->wsize.y / mlx->wsize.x);
	}
	if (button == 3)
	{
		wld->plr.fov.x = M_TAU / 4;
		wld->plr.fov.y = 2 * atan(tan(wld->plr.fov.x / 2) *
				mlx->wsize.y / mlx->wsize.x);
	}
	x++;
	y++;
	return (0);
}
