#include "wolf3d.h"
#include <stdio.h>														///debug

static void	*draw_thread(void *mlxt)
{
	t_mlx		*mlx;
	t_coord	px;
	unsigned int			ccolor;
	unsigned int			fcolor;
	t_col		col;
	// int lines = 0 ;

	mlx = ((t_mlx_thread *)mlxt)->mlx;
	px.x = ((t_mlx_thread *)mlxt)->y;
	// t_wld *wld= (t_wld *)mlx->data;
	// printf("in thread %d\n", px.x);																///deubg

	// printf("mlxt = %p, mlx = %p; img.start = %p; img.end = %p\n", mlxt, mlx, mlx->img.start, mlx->img.start + mlx->wsize.y * mlx->img.lsize);								//debug
	while (px.x < mlx->wsize.x)
	{
		// printf("thread = %d ", px.x % 4);
		col = get_column(px.x, mlx);

		// col.height = mlx->wsize.y / 2;
		ccolor = mlx_get_color_value(mlx->id, 0x7777FF);
		fcolor = mlx_get_color_value(mlx->id, 0x335533);
		px.y = ~0;


		while (++px.y < mlx->wsize.y / 2 - col.height)
		{
			// ccolor = 0xFF0000 >> (px.x % THREADS * 8);
			// printf("ccolor = %d; threads = %d\n", ccolor, THREADS);
			*((int *)(mlx->img.start + (px.y) * mlx->img.lsize) + px.x) = ccolor;
			// printf("fcolor = %d; threads = %d\n", fcolor, THREADS);
			*((int *)(mlx->img.start + (mlx->wsize.y - px.y - 1) * mlx->img.lsize) + px.x) = fcolor;

			// float angle = atan2(px.x - mlx->wsize.x / 2, mlx->wsize.x / tan(wld->plr.fov.x / 2));
			// float dist = (mlx->wsize.y / 2) / px.y / cos(angle) / tan(wld->plr.fov.y / 2);
			// int flrclr = mlx_get_color_value(mlx->id, 0 - ((int)(0x08 * dist) << 24));
			int flrclr = mlx_get_color_value(mlx->id, 0xFF000000);


			*((int *)(mlx->fog.start + (px.y) * mlx->fog.lsize) + px.x) = flrclr;
			*((int *)(mlx->fog.start + (mlx->wsize.y - px.y - 1) * mlx->fog.lsize) + px.x) = flrclr;
			// if (!(px.y % (mlx->wsize.y / 200)))
			// {
			// 	ccolor -= mlx_get_color_value(mlx->id, 0x010101);
			// 	fcolor -= mlx_get_color_value(mlx->id, 0x010101);
			// }
		}
		// *(int *)(mlx->img.start + (px.y) * mlx->img.lsize + px.x * 4) = 0;
		// *(int *)(mlx->img.start + (mlx->wsize.y - px.y) * mlx->img.lsize + px.x * 4) = 0;
		while (px.y < mlx->wsize.y / 2)
		{
			// color = 0xFF0000 >> (px.x % THREADS * 8);
			// printf("color = %d; threads = %d\n", color, THREADS);
			*((int *)(mlx->img.start + (px.y) * mlx->img.lsize) + px.x) = col.color;
			*((int *)(mlx->img.start + (px.y + col.height) * mlx->img.lsize) + px.x) = col.color;
			*((int *)(mlx->fog.start + (px.y) * mlx->fog.lsize) + px.x) = col.fogclr;
			*((int *)(mlx->fog.start + (px.y + col.height) * mlx->fog.lsize) + px.x) = col.fogclr;
			// *(int *)(mlx->img.start + (mlx->wsize.y - px.y) * mlx->img.lsize + px.x * 4) = col.color;
			px.y++;
		}
		// *(int *)(mlx->img.start + (px.y) * mlx->img.lsize + px.x * 4) = col.color;


		// while (++px.y < mlx->wsize.y)
		// {
		// 	// color = 0xFF0000 >> (px.x % THREADS * 8);
		// 	color = 0x777777;
		// 	// printf("color = %d; threads = %d\n", color, THREADS);
		// 	*(int *)(mlx->img.start + px.y * mlx->img.lsize + px.x * 4) = color;
		// }
		px.x += THREADS;
		// lines++;
	}
	// printf("lines drawn: %d\n", lines);
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
