/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:39:35 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:39:36 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	draw_col(t_col col, int x, t_mlx *mlx)
{
	int				y;
	unsigned int	flrfog;

	flrfog = mlx_get_color_value(mlx->id, 0xFF000000);
	y = ~0;
	while (++y < mlx->wsize.y / 2 - col.ht)
	{
		*((int *)(mlx->img.start + (y) * mlx->img.lsize) + x) =
				mlx_get_color_value(mlx->id, 0x7777FF);
		*((int *)(mlx->img.start + (mlx->wsize.y - y - 1) * mlx->img.lsize)
				+ x) = mlx_get_color_value(mlx->id, 0x335533);
		*((int *)(mlx->fog.start + (y) * mlx->fog.lsize) + x) = flrfog;
		*((int *)(mlx->fog.start + (mlx->wsize.y - y - 1) * mlx->fog.lsize)
				+ x) = flrfog;
	}
	while (y < mlx->wsize.y / 2)
	{
		*((int *)(mlx->img.start + y * mlx->img.lsize) + x) = col.clr;
		*((int *)(mlx->img.start + (y + col.ht) * mlx->img.lsize)
				+ x) = col.clr;
		*((int *)(mlx->fog.start + y * mlx->fog.lsize) + x) = col.fclr;
		*((int *)(mlx->fog.start + (y + col.ht) * mlx->fog.lsize)
				+ x) = col.fclr;
		y++;
	}
}

static void	*draw_thread(void *mlxt)
{
	t_mlx	*mlx;
	t_coord	px;
	t_col	col;

	mlx = ((t_mlx_thread *)mlxt)->mlx;
	px.x = ((t_mlx_thread *)mlxt)->y;
	while (px.x < mlx->wsize.x)
	{
		col = get_column(px.x, mlx);
		draw_col(col, px.x, mlx);
		px.x += THREADS;
	}
	return (NULL);
}

void		draw(t_mlx *mlx)
{
	t_mlx_thread	mlxt[THREADS];
	pthread_t		thread[THREADS];
	int				i;

	i = ~0;
	while (++i < THREADS)
	{
		mlxt[i].mlx = mlx;
		mlxt[i].y = i;
		pthread_create(&thread[i], NULL, draw_thread, &mlxt[i]);
	}
	i = ~0;
	while (++i < THREADS)
	{
		pthread_join(thread[i], NULL);
	}
	mlx_put_image_to_window(mlx->id, mlx->win, mlx->img.id, 0, 0);
	mlx_put_image_to_window(mlx->id, mlx->win, mlx->fog.id, 0, 0);
}
