/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:41:29 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:41:30 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			expose_hook(t_mlx *mlx)
{
	draw(mlx);
	return (0);
}

int			exit_hook(t_mlx *mlx)
{
	mlx_destroy_window(mlx->id, mlx->win);
	mlx_destroy_image(mlx->id, mlx->img.id);
	mlx_destroy_image(mlx->id, mlx->fog.id);
	free(mlx->id);
	ft_arrldel((void **)((t_wld *)(mlx->data))->map,
			((t_wld *)mlx->data)->size.y);
	exit(0);
	return (0);
}

/*
**	0: a
**	1: s
**	2: d
**	13: w
**	49: space
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
		plr->vel = add_vector(plr->vel, plr->rot, 0.01);
	if (mlx->keys[125] || mlx->keys[1])
		plr->vel = add_vector(plr->vel, plr->rot + M_TAU / 2, 0.01);
	if (mlx->keys[2])
		plr->vel = add_vector(plr->vel, plr->rot + M_TAU / 4, 0.01);
	if (mlx->keys[0])
		plr->vel = add_vector(plr->vel, plr->rot - M_TAU / 4, 0.01);
	if (mlx->keys[123])
		plr->rot -= plr->fov.x / 32;
	if (mlx->keys[124])
		plr->rot += plr->fov.x / 32;
}

static void	move_player(t_plr *plr, t_vec vel)
{
	plr->pos.y += sin(vel.dir) * vel.mag;
	plr->pos.x += cos(vel.dir) * vel.mag;
}

int			loop_hook(t_mlx *mlx)
{
	handle_keys(mlx);
	move_player(&((t_wld *)(mlx->data))->plr, ((t_wld *)(mlx->data))->plr.vel);
	((t_wld *)(mlx->data))->plr.vel.mag *= .91;
	draw(mlx);
	return (0);
}
