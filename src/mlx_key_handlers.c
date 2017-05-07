/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_key_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:24:51 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:24:53 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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

int	key_press_hook(int key_code, t_mlx *mlx)
{
	if (key_code >= 0 && key_code <= MAXKEYS)
	{
		mlx->keys[key_code] = 1;
	}
	return (0);
}

int	key_release_hook(int key_code, t_mlx *mlx)
{
	if (key_code >= 0 && key_code <= MAXKEYS)
	{
		mlx->keys[key_code] = 0;
	}
	if (key_code == 53)
	{
		mlx_destroy_window(mlx->id, mlx->win);
		mlx_destroy_image(mlx->id, mlx->img.id);
		mlx_destroy_image(mlx->id, mlx->fog.id);
		free(mlx->id);
		ft_arrldel((void **)((t_wld *)(mlx->data))->map,
				((t_wld *)mlx->data)->size.y);
		exit(0);
	}
	return (0);
}
