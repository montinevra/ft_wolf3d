#include "wolf3d.h"
#include <stdio.h>																							///debug

int	expose_hook(t_mlx *mlx)
{
	draw(mlx);
	return (0);
}

int	exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->id, mlx->win);
	mlx_destroy_image(mlx->id, mlx->img.id);
	free(mlx->id);
	ft_arrldel((void **)((t_wld *)(mlx->data))->map, ((t_wld *)mlx->data)->size.y);
	exit(0);
	return (0);
}

static void	move_player(t_plr *plr, t_vel vel)
{
	plr->pos.y += sin(vel.dir) * vel.mag;
	plr->pos.x += cos(vel.dir) * vel.mag;
}


int	loop_hook(t_mlx *mlx)
{
	// static int i;
	move_player(&((t_wld *)(mlx->data))->plr, ((t_wld *)(mlx->data))->plr.vel);
	((t_wld *)(mlx->data))->plr.vel.mag *= .95;
	// printf("%d\n", i++);
	draw(mlx);	
	return (0);
}