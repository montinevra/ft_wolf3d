#include "wolf3d.h"
#include <stdio.h>																							///debug

int			motion_hook(int x, int y, t_mlx *mlx)
{
	// ((t_frac *)mlx->data)->c.a = x * mlx->scale - mlx->offset.a;
	// ((t_frac *)mlx->data)->c.b = -(y * mlx->scale - mlx->offset.b);
	// draw(mlx);
	x++;																							//debug
	y++;																							//debug
	mlx++;																							//debug
	return (0);
}

/*
**	1: left
**	2: right
**	3: middle/thumbs
**	4: scroll up
**	5: scroll down
*/

int			mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	t_wld	*wld;

	wld = (t_wld *)mlx->data;
	// if (y >= 0)
	// {
	// 	if (button == 1)
	// 		((t_frac *)mlx->data)->i_max++;
	// 	else if (button == 2)
	// 		((t_frac *)mlx->data)->i_max--;
	if (button == 4)
	{
		wld->plr.fov.x *= .9;
		if (wld->plr.fov.x < M_TAU / 180)
			wld->plr.fov.x = M_TAU / 180;
		wld->plr.fov.y = 2 * atan(tan(wld->plr.fov.x / 2) * mlx->wsize.y / mlx->wsize.x);
	}
	if (button == 5)
	{
		wld->plr.fov.x /= .9;
		if (wld->plr.fov.x > M_TAU / 2.1)
			wld->plr.fov.x = M_TAU / 2.1;
		wld->plr.fov.y = 2 * atan(tan(wld->plr.fov.x / 2) * mlx->wsize.y / mlx->wsize.x);
	}
	// 	else if (button == 3)
	// 		init_scale(mlx);
	// 	if (button >= 1 && button <= 5)
	// 	{
	// 		if (((t_frac *)mlx->data)->i_max == 0)
	// 			((t_frac *)mlx->data)->i_max = 1;
	// 		draw(mlx);
	// 	}
	// }
	x++;																										//debug
	y++;																										//debug
	return (0);
}

