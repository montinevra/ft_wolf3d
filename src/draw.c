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
	t_world	wld;
	t_pos	h;
	double	sidex;
	double	sidey;
	t_coord	map;
	int 	side;
	t_coord	step;


	wld = *((t_world *)mlx->data);
	angle = wld.plr.fov.x * col / mlx->wsize.x - wld.plr.fov.x / 2;
	// printf("angle = %f\n", angle);																				//debug
	h.x = 1.0 / cos(angle + wld.plr.rot);
	h.y = 1.0 / sin(angle + wld.plr.rot);
	map.x = floor(wld.plr.pos.x);
	map.y = floor(wld.plr.pos.y);
	if (h.x >= 0)
	{
		step.x = 1;
		sidex = (map.x + 1 - wld.plr.pos.x) * h.x;
	}
	else
	{
		step.x = -1;
		sidex = (wld.plr.pos.x - map.x) * h.x;
	}
	if (h.y >= 0)
	{
		step.y = 1;
		sidey = (map.y + 1 - wld.plr.pos.y) * h.y;
	}
	else
	{
		step.y = -1;
		sidey = (wld.plr.pos.y - map.y) * h.y;
	}
	// printf("currently in %d, %d\n", map.x, map.y);
	// printf("my position %f, %f            ", wld.plr.pos.x, wld.plr.pos.y);												//debug

	while (map.y >= 0 && map.x >= 0 && map.y < wld.size.y && map.x < wld.size.x && wld.map[map.y][map.x] != '1' )
	{
		// printf("testing %d, %d...\n", map.x, map.y);
		if (fabs(sidex) < fabs(sidey))
		{
			sidex += h.x;
			map.x += step.x;
			side = 0;
		}
		else
		{
			sidey += h.y;
			map.y += step.y;
			side = 1;
		}
	} 
		// printf("wld.plr.fov.y = %f, tan = %f\n", wld.plr.fov.y, tan(wld.plr.fov.y));
	column.color = map.y * 16 + ((map.x * 16) << 16);
	if (side)
	{
		// printf("SIDEY = %f; SIDEX = %f\n", sidey, sidex);													//debug
		column.color += 0x111111;
		column.height = fabs((mlx->wsize.x / 2) / (sidey * cos(angle) * tan(wld.plr.fov.y / 2)));
	}
	else
	{
		// printf("sidex = %f; sidey = %f\n", sidex, sidey);													//debug
		column.height = fabs((mlx->wsize.x / 2) / (sidex * cos(angle) * tan(wld.plr.fov.y / 2)));
	}
	// printf("column.height = %d\n", column.height);
	// column.height = 100;
	return (column);
}

static void	*draw_thread(void *mlxt)
{
	t_mlx		*mlx;
	t_coord	px;
	int			ccolor;
	int			fcolor;
	t_col		col;
	// int lines = 0 ;

	mlx = ((t_mlx_thread *)mlxt)->mlx;
	px.x = ((t_mlx_thread *)mlxt)->y;
	// printf("in thread %d\n", px.x);																///deubg
	while (px.x < mlx->wsize.x)
	{
		////hack to eliminate bad heights. should not be necessary once height algorithm works
		col = get_column(px.x, mlx);
		if (col.height < 0)
		{
			// printf("bad height: %d\n", col.height);													///debug
			col.height = 0;
		}
		else if (col.height > mlx->wsize.y / 2)
		{
			printf("bad height: %d\n", col.height);													///debug
			col.height = mlx->wsize.y / 2;
		}
		// col.height = mlx->wsize.y / 2;
		px.y = ~0;
		ccolor = 0x777777;
		fcolor = 0x777777;
		while (++px.y < mlx->wsize.y / 2 - col.height)
		{
			// ccolor = 0xFF0000 >> (px.x % THREADS * 8);
			// printf("ccolor = %d; threads = %d\n", ccolor, THREADS);
			*(int *)(mlx->img.start + px.y * mlx->img.lsize + px.x * 4) = ccolor;
			// printf("fcolor = %d; threads = %d\n", fcolor, THREADS);
			*(int *)(mlx->img.start + (mlx->wsize.y - px.y) * mlx->img.lsize + px.x * 4) = fcolor;
			if (!(px.y % (mlx->wsize.y / 128)))
			{
				ccolor -= 0x010101;
				fcolor -= 0x010101;
			}
		}
		*(int *)(mlx->img.start + px.y * mlx->img.lsize + px.x * 4) = 0;
		*(int *)(mlx->img.start + (mlx->wsize.y - px.y) * mlx->img.lsize + px.x * 4) = 0;
		while (++px.y < mlx->wsize.y / 2)
		{
			// color = 0xFF0000 >> (px.x % THREADS * 8);
			// printf("color = %d; threads = %d\n", color, THREADS);
			*(int *)(mlx->img.start + px.y * mlx->img.lsize + px.x * 4) = col.color;
			*(int *)(mlx->img.start + (mlx->wsize.y - px.y) * mlx->img.lsize + px.x * 4) = col.color;
		}
		*(int *)(mlx->img.start + px.y * mlx->img.lsize + px.x * 4) = col.color;
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
	// pthread_t		thread[THREADS];
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
		// pthread_create(&thread[i], NULL, draw_thread, &mlxt[i]);
		draw_thread(&mlxt[i]);
	}
	// i = ~0;
	// while (++i < THREADS)
	// {
	// 	pthread_join(thread[i], NULL);
	// 	// printf("thread %d finished\n", i);													////debug
	// }



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

	t_world	*wld = (t_world *)mlx->data;																//debug
	printf("player pos = %f, %f rot = %f\n", wld->plr.pos.x, wld->plr.pos.y, wld->plr.rot);							//debug

}
