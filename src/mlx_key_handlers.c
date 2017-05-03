#include "wolf3d.h"
#include <stdio.h>																							///debug

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
		mlx_destroy_window(mlx->id, mlx->win);
		mlx_destroy_image(mlx->id, mlx->img.id);
		free(mlx->id);
		ft_arrldel((void **)((t_wld *)(mlx->data))->map, ((t_wld *)mlx->data)->size.y);
		exit(0);
	}
	// else
	// {
	// 	if (key_code == 0)
	// 		((t_wld *)(mlx->data))->plr.pos.y -= 0.1;
	// 	else if (key_code == 1)
	// 		((t_wld *)(mlx->data))->plr.pos.x -= 0.1;
	// 	else if (key_code == 2)
	// 		((t_wld *)(mlx->data))->plr.pos.y += 0.1;
	// 	else if (key_code == 13)
	// 		((t_wld *)(mlx->data))->plr.pos.x += 0.1;
	// 	else if (key_code == 123)
	// 		((t_wld *)(mlx->data))->plr.rot -= 0.1;
	// 	else if (key_code == 124)
	// 		((t_wld *)(mlx->data))->plr.rot += 0.1;
	// 	// else if (key_code == 125)
	// 	// 	mlx->offset.b += 10 * mlx->scale;
	// 	// else if (key_code == 126)
	// 	// 	mlx->offset.b -= 10 * mlx->scale;
		// draw(mlx);
	// }
	// printf("key = %d\n", key_code);																		////debug
	return (0);
}

void		move_player(t_mlx *mlx, double bearing)
{
	((t_wld *)(mlx->data))->plr.pos.y += sin(bearing) * 0.1;
	((t_wld *)(mlx->data))->plr.pos.x += cos(bearing) * 0.1;
}

int			key_press_hook(int key_code, t_mlx *mlx)
{

	if (key_code >= 0 && key_code <= MAXKEYS)
	{
		printf("key pressed!\n");
		mlx->keys[key_code] = 1;
	}
	// if (key_code == 0)
	// {
	// 	move_player(mlx, ((t_wld *)(mlx->data))->plr.rot - M_TAU / 4);
	// 	// ((t_wld *)(mlx->data))->plr.pos.y -= 0.1;
	// }
	// else if (key_code == 1 || key_code == 125)
	// {
	// 	move_player(mlx, ((t_wld *)(mlx->data))->plr.rot + M_TAU / 2);
	// 	// ((t_wld *)(mlx->data))->plr.pos.x -= 0.1;
	// }
	// else if (key_code == 2)
	// {
	// 	move_player(mlx, ((t_wld *)(mlx->data))->plr.rot + M_TAU / 4);
	// 	// ((t_wld *)(mlx->data))->plr.pos.y += 0.1;
	// }
	// else if (key_code == 13 || key_code == 126)
	// {
	// 	move_player(mlx, ((t_wld *)(mlx->data))->plr.rot);
	// 	// ((t_wld *)(mlx->data))->plr.pos.x += 0.1;
	// }
	// else if (key_code == 123)
	// {
	// 	((t_wld *)(mlx->data))->plr.rot -= 0.1;
	// }
	// else if (key_code == 124)
	// {
	// 	((t_wld *)(mlx->data))->plr.rot += 0.1;
	// }
	// else if (key_code == 125)
	// 	mlx->offset.b += 10 * mlx->scale;
	// else if (key_code == 126)
	// 	mlx->offset.b -= 10 * mlx->scale;
	// draw(mlx);
	// printf("key = %d\n", key_code);																		////debug

	return (0);
}

int			key_release_hook(int key_code, t_mlx *mlx)
{
	if (key_code >= 0 && key_code <= MAXKEYS)
	{
		printf("key reelased!\n");
		mlx->keys[key_code] = 0;
	}
	if (key_code == 53)
	{
		mlx_destroy_window(mlx->id, mlx->win);
		mlx_destroy_image(mlx->id, mlx->img.id);
		free(mlx->id);
		ft_arrldel((void **)((t_wld *)(mlx->data))->map, ((t_wld *)mlx->data)->size.y);
		exit(0);
	}
	// if (key_code == 53)
	// {
	// 	free(mlx->img.id);
	// 	// free(mlx->data);
	// 	free(mlx->win);
	// 	free(mlx->id);
	// 	exit(0);
	// }
	// if (key_code == 123)
	// 	((t_wld *)(mlx->data))->plr.rot -= 0.1;
	// else if (key_code == 124)
	// 	((t_wld *)(mlx->data))->plr.rot += 0.1;
	// else if (key_code == 125)
	// 	mlx->offset.b += 10 * mlx->scale;
	// else if (key_code == 126)
	// 	mlx->offset.b -= 10 * mlx->scale;
	// draw(mlx);
	// printf("key = %d\n", key_code);																		////debug
	return (0);
}

