#include "wolf3d.h"
#include <stdio.h>														///debug

// static int	get_clr(int h)
// {
// 	int	r;
// 	int	g;
// 	int	b;

// 	r = 0;
// 	g = 0;
// 	b = 0;
// 	if (h <= 0xFF)
// 		b = h;
// 	else if (h <= 0xFF * 2)
// 	{
// 		r = h - 0xFF;
// 		g = h - 0xFF;
// 		b = 0xFF;
// 	}
// 	else if (h <= 0xFF * 3)
// 	{
// 		r = 0xFF;
// 		g = 0xFF * 3 - h;
// 		b = 0xFF * 3 - h;
// 	}
// 	else
// 		return (0);
// 	return (((r << 16) + (g << 8) + b));
// }




static t_col	get_column(int col, t_mlx *mlx)
{
	t_col	column;
	double	angle;
	t_wld	wld;
	t_pos	h;
	t_pos	dist;
	// double	dist.y;
	t_coord	map;
	int 	hside;
	t_coord	step;
	// char	tile;

	// col /= 16;
	// col *= 16;
	wld = *((t_wld *)mlx->data);


	double adj = mlx->wsize.x / tan(wld.plr.fov.x / 2);
	double opp = col - mlx->wsize.x / 2;
	angle = atan2(opp, adj);


	// angle = wld.plr.fov.x * col / mlx->wsize.x - wld.plr.fov.x / 2;



	// printf("angle = %f\n", angle + wld.plr.rot);																				//debug
	h.x = 1.0 / cos(angle + wld.plr.rot);
	h.y = 1.0 / sin(angle + wld.plr.rot);
	map.x = floor(wld.plr.pos.x);
	map.y = floor(wld.plr.pos.y);
	if (h.x >= 0)
	{
		step.x = 1;
		dist.x = (map.x + 1 - wld.plr.pos.x) * h.x;
	}
	else
	{
		step.x = -1;
		dist.x = (wld.plr.pos.x - map.x) * h.x;
	}
	if (h.y >= 0)
	{
		step.y = 1;
		dist.y = (map.y + 1 - wld.plr.pos.y) * h.y;
	}
	else
	{
		step.y = -1;
		dist.y = (wld.plr.pos.y - map.y) * h.y;
	}
	// printf("dist.x start = %lf; dist.y start = %lf\n", dist.x, dist.y);							//debug
	// printf("currently in %d, %d\n", map.x, map.y);
	// printf("my position %f, %f            ", wld.plr.pos.x, wld.plr.pos.y);												//debug
	hside = 0;
	// map.x -= step.x;
	// map.y -= step.y;
	// tile = wld.map[map.y][map.x];

	while (map.y >= 0 && map.x >= 0 && map.y < wld.size.y && map.x < wld.size.x && wld.map[map.y][map.x] == '1' )
	{
		// printf("testing %d, %d...\n", map.x, map.y);
		if (fabs(dist.x) < fabs(dist.y))
		{
			dist.x += h.x;
			map.x += step.x;
			hside = 0;
		}
		else
		{
			dist.y += h.y;
			map.y += step.y;
			hside = 1;
		}
	} 
	while (map.y >= 0 && map.x >= 0 && map.y < wld.size.y && map.x < wld.size.x && wld.map[map.y][map.x] != '1' )
	{
		// printf("testing %d, %d...\n", map.x, map.y);
		if (fabs(dist.x) < fabs(dist.y))
		{
			dist.x += h.x;
			map.x += step.x;
			hside = 0;
		}
		else
		{
			dist.y += h.y;
			map.y += step.y;
			hside = 1;
		}
	} 
	dist.x = fabs(dist.x - h.x);
	dist.y = fabs(dist.y - h.y);
		// printf("wld.plr.fov.y = %f, tan = %f\n", wld.plr.fov.y, tan(wld.plr.fov.y));
	column.color = mlx_get_color_value(mlx->id, map.y * 32 + ((map.x * 32) << 16));
	// column.color = 0XAAAAAA;
	if (hside)
	{
		// printf("dist.Y = %f; dist.X = %f\n", dist.y, dist.x);													//debug
		

		// column.color -= 0x4 * (int)dist.y + ((0x4 * (int)dist.y) << 8) + ((0x4 * (int)dist.y) << 16);

		column.color += mlx_get_color_value(mlx->id, 0x111111);
		// int i = ~0;
		// while (++i < 3)
		// {
		// 	*((char *)&column.color + i) -= 0x01 * floor(dist.y);
		// 	if (*((char *)&column.color + i) < 0)
		// 		*((char *)&column.color + i) = 0;
		// }
		// column.color -= mlx_get_color_value(mlx->id, 0x010101 * floor(dist.y));

		// dist.y = (map.y - wld.plr.pos.y) / sin(angle + wld.plr.rot);
		column.height = ((mlx->wsize.y / 2) / (dist.y * cos(angle) * tan(wld.plr.fov.y / 2)));
	}
	else
	{
		// printf("dist.x = %f; dist.y = %f\n", dist.x, dist.y);													//debug
		// dist.x = (map.x - wld.plr.pos.x) / cos(angle + wld.plr.rot);

		// column.color -= mlx_get_color_value(mlx->id, 0x010101 * floor(dist.x));


		column.height = ((mlx->wsize.y / 2) / (dist.x * cos(angle) * tan(wld.plr.fov.y / 2)));
	}
	// printf("column.height = %d\n", column.height);
	// column.height = 1100;
	if (column.height < 0)
	{
		// printf("bad height: %d\n", column.height);													///debug
		column.height = 0;
	}
	else if (column.height > mlx->wsize.y / 2)
	{
		// printf("bad height: %d\n", column.height);													///debug
		column.height = mlx->wsize.y / 2;
	}	return (column);
}

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
	// printf("in thread %d\n", px.x);																///deubg
	
	// printf("mlxt = %p, mlx = %p; img.start = %p; img.end = %p\n", mlxt, mlx, mlx->img.start, mlx->img.start + mlx->wsize.y * mlx->img.lsize);								//debug
	while (px.x < mlx->wsize.x)
	{
		// printf("thread = %d ", px.x % 4);
		col = get_column(px.x, mlx);

		// col.height = mlx->wsize.y / 2;
		ccolor = mlx_get_color_value(mlx->id, 0x777777);
		fcolor = mlx_get_color_value(mlx->id, 0x777777);
		px.y = ~0;


		while (++px.y < mlx->wsize.y / 2 - col.height)
		{
			// ccolor = 0xFF0000 >> (px.x % THREADS * 8);
			// printf("ccolor = %d; threads = %d\n", ccolor, THREADS);
			*((int *)(mlx->img.start + (px.y) * mlx->img.lsize) + px.x) = ccolor;
			// printf("fcolor = %d; threads = %d\n", fcolor, THREADS);
			*((int *)(mlx->img.start + (mlx->wsize.y - px.y - 1) * mlx->img.lsize) + px.x) = fcolor;
			if (!(px.y % (mlx->wsize.y / 128)))
			{
				ccolor -= mlx_get_color_value(mlx->id, 0x010101);
				fcolor -= mlx_get_color_value(mlx->id, 0x010101);
			}
		}
		// *(int *)(mlx->img.start + (px.y) * mlx->img.lsize + px.x * 4) = 0;
		// *(int *)(mlx->img.start + (mlx->wsize.y - px.y) * mlx->img.lsize + px.x * 4) = 0;
		while (px.y < mlx->wsize.y / 2)
		{
			// color = 0xFF0000 >> (px.x % THREADS * 8);
			// printf("color = %d; threads = %d\n", color, THREADS);
			*((int *)(mlx->img.start + (px.y) * mlx->img.lsize) + px.x) = col.color;
			*((int *)(mlx->img.start + (px.y + col.height) * mlx->img.lsize) + px.x) = col.color;
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

	// t_wld	*wld = (t_wld *)mlx->data;																//debug
	// printf("player pos = %f, %f rot = %f\n", wld->plr.pos.x, wld->plr.pos.y, wld->plr.rot);							//debug

}
