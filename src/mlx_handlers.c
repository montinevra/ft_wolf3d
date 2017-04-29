#include "wolf3d.h"
#include <stdio.h>																							///debug
// static void	zoom(int button, int x, int y, t_mlx *mlx)
// {
// 	long double	oldscale;

// 	oldscale = mlx->scale;
// 	if (button == 5)
// 		mlx->scale *= mlx->scalefr;
// 	else if (button == 4)
// 		mlx->scale /= mlx->scalefr;
// 	mlx->offset.a += x * (mlx->scale - oldscale);
// 	mlx->offset.b += y * (mlx->scale - oldscale);
// }

int			expose_hook(t_mlx *mlx)
{
	draw(mlx);
	return (0);
}

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
	// if (y >= 0)
	// {
	// 	if (button == 1)
	// 		((t_frac *)mlx->data)->i_max++;
	// 	else if (button == 2)
	// 		((t_frac *)mlx->data)->i_max--;
	// 	else if (button == 4 || button == 5)
	// 		zoom(button, x, y, mlx);
	// 	else if (button == 3)
	// 		init_scale(mlx);
	// 	if (button >= 1 && button <= 5)
	// 	{
	// 		if (((t_frac *)mlx->data)->i_max == 0)
	// 			((t_frac *)mlx->data)->i_max = 1;
	// 		draw(mlx);
	// 	}
	// }
	button++;																										//debug
	x++;																										//debug
	y++;																										//debug
	mlx++;																										//debug
	return (0);
}

/*
**	0: a
**	1: s
**	2: d
**	13: w
**123: left
**124: right
**125: down
**126: up
*/

int			key_hook(int key_code, t_mlx *mlx)
{
	if (key_code == 53)
	{
		free(mlx->img.id);
		// free(mlx->data);
		free(mlx->win);
		free(mlx->id);
		// int i = ~0;
		// t_world *wld = (t_world *)mlx->data;
		// while (++i < wld->size.y)
		// 	free(wld->map[i]);
		ft_arrldel((void **)((t_world *)(mlx->data))->map, ((t_world *)mlx->data)->size.y);
		// free(wld->map);
		exit(0);
	}
	// else
	// {
	// 	if (key_code == 0)
	// 		((t_world *)(mlx->data))->plr.pos.y -= 0.1;
	// 	else if (key_code == 1)
	// 		((t_world *)(mlx->data))->plr.pos.x -= 0.1;
	// 	else if (key_code == 2)
	// 		((t_world *)(mlx->data))->plr.pos.y += 0.1;
	// 	else if (key_code == 13)
	// 		((t_world *)(mlx->data))->plr.pos.x += 0.1;
	// 	else if (key_code == 123)
	// 		((t_world *)(mlx->data))->plr.rot -= 0.1;
	// 	else if (key_code == 124)
	// 		((t_world *)(mlx->data))->plr.rot += 0.1;
	// 	// else if (key_code == 125)
	// 	// 	mlx->offset.b += 10 * mlx->scale;
	// 	// else if (key_code == 126)
	// 	// 	mlx->offset.b -= 10 * mlx->scale;
	// 	draw(mlx);
	// }
	// printf("key = %d\n", key_code);																		////debug
	return (0);
}

void		move_player(t_mlx *mlx, double bearing)
{
	((t_world *)(mlx->data))->plr.pos.y += sin(bearing) * 0.1;
	((t_world *)(mlx->data))->plr.pos.x += cos(bearing) * 0.1;
}

int			key_press_hook(int key_code, t_mlx *mlx)
{

	if (key_code >= 0 && key_code <= MAXKEYS)
		((t_world *)(mlx->data))->keys[key_code] = 1;
	if (key_code == 0)
	{
		move_player(mlx, ((t_world *)(mlx->data))->plr.rot - M_TAU / 4);
		// ((t_world *)(mlx->data))->plr.pos.y -= 0.1;
	}
	else if (key_code == 1 || key_code == 125)
	{
		move_player(mlx, ((t_world *)(mlx->data))->plr.rot + M_TAU / 2);
		// ((t_world *)(mlx->data))->plr.pos.x -= 0.1;
	}
	else if (key_code == 2)
	{
		move_player(mlx, ((t_world *)(mlx->data))->plr.rot + M_TAU / 4);
		// ((t_world *)(mlx->data))->plr.pos.y += 0.1;
	}
	else if (key_code == 13 || key_code == 126)
	{
		move_player(mlx, ((t_world *)(mlx->data))->plr.rot);
		// ((t_world *)(mlx->data))->plr.pos.x += 0.1;
	}
	else if (key_code == 123)
	{
		((t_world *)(mlx->data))->plr.rot -= 0.1;
	}
	else if (key_code == 124)
	{
		((t_world *)(mlx->data))->plr.rot += 0.1;
	}
	// else if (key_code == 125)
	// 	mlx->offset.b += 10 * mlx->scale;
	// else if (key_code == 126)
	// 	mlx->offset.b -= 10 * mlx->scale;
	draw(mlx);
	// printf("key = %d\n", key_code);																		////debug

	return (0);
}

int			key_release_hook(int key_code, t_mlx *mlx)
{
	if (key_code >= 0 && key_code <= MAXKEYS)
		((t_world *)(mlx->data))->keys[key_code] = 0;
	// if (key_code == 53)
	// {
	// 	free(mlx->img.id);
	// 	// free(mlx->data);
	// 	free(mlx->win);
	// 	free(mlx->id);
	// 	exit(0);
	// }
	// if (key_code == 123)
	// 	((t_world *)(mlx->data))->plr.rot -= 0.1;
	// else if (key_code == 124)
	// 	((t_world *)(mlx->data))->plr.rot += 0.1;
	// else if (key_code == 125)
	// 	mlx->offset.b += 10 * mlx->scale;
	// else if (key_code == 126)
	// 	mlx->offset.b -= 10 * mlx->scale;
	// draw(mlx);
	// printf("key = %d\n", key_code);																		////debug
	return (0);
}

