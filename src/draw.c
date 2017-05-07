#include "wolf3d.h"
#include <stdio.h>														///debug

static void	draw_col(t_col col, int x, t_mlx *mlx)
{
	int				y;
	unsigned int	ccolor;
	unsigned int	fcolor;
	unsigned int	flrfog;

	flrfog = mlx_get_color_value(mlx->id, 0xFF000000);
	ccolor = mlx_get_color_value(mlx->id, 0x7777FF);
	fcolor = mlx_get_color_value(mlx->id, 0x335533);
	y = ~0;
	while (++y < mlx->wsize.y / 2 - col.height)
	{
		*((int *)(mlx->img.start + (y) * mlx->img.lsize) + x) = ccolor;
		*((int *)(mlx->img.start + (mlx->wsize.y - y - 1) * mlx->img.lsize) + x) = fcolor;
		*((int *)(mlx->fog.start + (y) * mlx->fog.lsize) + x) = flrfog;
		*((int *)(mlx->fog.start + (mlx->wsize.y - y - 1) * mlx->fog.lsize) + x) = flrfog;
	}
	while (y < mlx->wsize.y / 2)
	{
		*((int *)(mlx->img.start + (y) * mlx->img.lsize) + x) = col.color;
		*((int *)(mlx->img.start + (y + col.height) * mlx->img.lsize) + x) = col.color;
		*((int *)(mlx->fog.start + (y) * mlx->fog.lsize) + x) = col.fogclr;
		*((int *)(mlx->fog.start + (y + col.height) * mlx->fog.lsize) + x) = col.fogclr;
		y++;
	}
}

static void	*draw_thread(void *mlxt)
{
	t_mlx		*mlx;
	t_coord	px;
	t_col		col;

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

	// printf("drawing.....\n");									//debug
	// mlxt.mlx = mlx;
	// mlxt.y = ~0;


	i = ~0;
	while (++i < THREADS)
	{
		mlxt[i].mlx = mlx;
		mlxt[i].y = i;
		// printf("thread %d starting\n", i);													////debug
		pthread_create(&thread[i], NULL, draw_thread, &mlxt[i]);
		// draw_thread(&mlxt[i]);
	}
	i = ~0;
	while (++i < THREADS)
	{
		pthread_join(thread[i], NULL);
		// printf("thread %d finished\n", i);													////debug
	}



	/*																					debug
	int j = ~0;
	while (++j < mlx->wsize.x)
	{
		int i = ~0;
		while (++i < mlx->wsize.x)
		{
			printf("%x ", *(int *)(mlx->img.start + j * mlx->img.lsize + i * 4));
		}
		printf("\n");
	}
	// */

	mlx_put_image_to_window(mlx->id, mlx->win, mlx->img.id, 0, 0);
	mlx_put_image_to_window(mlx->id, mlx->win, mlx->fog.id, 0, 0);

	// t_wld	*wld = (t_wld *)mlx->data;																//debug
	// printf("player pos = %f, %f rot = %f\n", wld->plr.pos.x, wld->plr.pos.y, wld->plr.rot);							//debug

}
