#include "wolf3d.h"
#include <stdio.h>																							///debug

int	expose_hook(t_mlx *mlx)
{
	// draw(mlx);
	mlx++;
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

static void	handle_keys(t_mlx *mlx)
{
	t_plr	*plr;

	plr = &((t_wld *)(mlx->data))->plr;

	if (mlx->keys[126] || mlx->keys[13])
	{
		// printf("key is pressed\n");
		plr->vel = add_vector(plr->vel, plr->rot, 0.01);
	}
	if (mlx->keys[125] || mlx->keys[1])
	{
		// printf("key is pressed\n");
		plr->vel = add_vector(plr->vel, plr->rot + M_TAU / 2, 0.01);
	}
	if (mlx->keys[2])
	{
		// printf("key is pressed\n");
		plr->vel = add_vector(plr->vel, plr->rot + M_TAU / 4, 0.01);
	}
	if (mlx->keys[0])
	{
		// printf("key is pressed\n");
		plr->vel = add_vector(plr->vel, plr->rot - M_TAU / 4, 0.01);
	}
	if (mlx->keys[123])
	{
		// printf("key is pressed\n");
		plr->rot -= 0.05;
	}
	if (mlx->keys[124])
	{
		// printf("key is pressed\n");
		plr->rot += 0.05;
	}

}


static void	move_player(t_plr *plr, t_vec vel)
{
	plr->pos.y += sin(vel.dir) * vel.mag;
	plr->pos.x += cos(vel.dir) * vel.mag;
}


int	loop_hook(t_mlx *mlx)
{
	// static int i;
	handle_keys(mlx);
	move_player(&((t_wld *)(mlx->data))->plr, ((t_wld *)(mlx->data))->plr.vel);
	((t_wld *)(mlx->data))->plr.vel.mag *= .91;
	// printf("%d\n", i++);
	draw(mlx);	
	return (0);
}