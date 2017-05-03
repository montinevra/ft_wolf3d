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


static t_ray	ray_start(t_ray ray, t_coord grid, t_wld wld)
{
	if (ray.hyp.x >= 0)
	{
		ray.step.x = 1;
		ray.dist.x = (grid.x + 1 - wld.plr.pos.x) * ray.hyp.x;
	}
	else
	{
		ray.step.x = -1;
		ray.dist.x = (wld.plr.pos.x - grid.x) * ray.hyp.x;
	}
	if (ray.hyp.y >= 0)
	{
		ray.step.y = 1;
		ray.dist.y = (grid.y + 1 - wld.plr.pos.y) * ray.hyp.y;
	}
	else
	{
		ray.step.y = -1;
		ray.dist.y = (wld.plr.pos.y - grid.y) * ray.hyp.y;
	}
	return (ray);
}

static int		cast(t_ray *ray, t_coord *grid, t_wld wld, char *tiles)
{
	int	hside;

	hside = 0;
	while (grid->y >= 0 && grid->x >= 0 && grid->y < wld.size.y && grid->x < wld.size.x)
	{
		if (ft_strchr(tiles, wld.map[grid->y][grid->x]))
			break ;
		// printf("testing %d, %d...\n", grid->x, grid->y);
		if (fabs(ray->dist.x) < fabs(ray->dist.y))
		{
			ray->dist.x += ray->hyp.x;
			grid->x += ray->step.x;
			hside = 0;
		}
		else
		{
			ray->dist.y += ray->hyp.y;
			grid->y += ray->step.y;
			hside = 1;
		}
	}
	return (hside);
}

static t_col	get_column(int col, t_mlx *mlx)
{
	t_col	column;
	double	angle;
	t_wld	wld;
	t_ray	ray;
	// t_pos	ray.hyp;
	// t_pos	ray.dist;
	// double	ray.dist.y;
	t_coord	grid;
	int 	hside;
	// t_coord	ray.step;

	wld = *((t_wld *)mlx->data);
	angle = atan2(col - mlx->wsize.x / 2, mlx->wsize.x / tan(wld.plr.fov.x / 2));

	// printf("angle = %f\n", angle + wld.plr.rot);																				//debug
	ray.hyp.x = 1.0 / cos(angle + wld.plr.rot);
	ray.hyp.y = 1.0 / sin(angle + wld.plr.rot);
	grid.x = floor(wld.plr.pos.x);
	grid.y = floor(wld.plr.pos.y);
	ray = ray_start(ray, grid, wld);
	// printf("ray.dist.x start = %lf; ray.dist.y start = %lf\n", ray.dist.x, ray.dist.y);							//debug
	// printf("currently in %d, %d\n", grid.x, grid.y);
	// printf("my position %f, %f            ", wld.plr.pos.x, wld.plr.pos.y);												//debug
	hside = 0;
	// grid.x -= ray.step.x;
	// grid.y -= ray.step.y;
	// tile = wld.grid[grid.y][grid.x];

	cast(&ray, &grid, wld, "02");
	hside = cast(&ray, &grid, wld, "1");

	ray.dist.x = fabs(ray.dist.x - ray.hyp.x);
	ray.dist.y = fabs(ray.dist.y - ray.hyp.y);
		// printf("wld.plr.fov.y = %f, tan = %f\n", wld.plr.fov.y, tan(wld.plr.fov.y));
	column.color = mlx_get_color_value(mlx->id, grid.y * 32 + ((grid.x * 32) << 16));
	// column.color = 0XAAAAAA;
	if (hside)
	{
		// printf("ray.dist.Y = %f; ray.dist.X = %f\n", ray.dist.y, ray.dist.x);													//debug
		

		column.color += mlx_get_color_value(mlx->id, 0x111111);
		column.fogclr = mlx_get_color_value(mlx->id, 0 - ((int)(0x08 * ray.dist.y) << 24));
		column.height = ((mlx->wsize.y / 2) / (ray.dist.y * cos(angle) * tan(wld.plr.fov.y / 2)));
	}
	else
	{
		// printf("ray.dist.x = %f; ray.dist.y = %f\n", ray.dist.x, ray.dist.y);													//debug

		column.fogclr = mlx_get_color_value(mlx->id, 0 - ((int)(0x08 * ray.dist.x) << 24));
		column.height = ((mlx->wsize.y / 2) / (ray.dist.x * cos(angle) * tan(wld.plr.fov.y / 2)));
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
			*((int *)(mlx->fog.start + (px.y) * mlx->fog.lsize) + px.x) = mlx_get_color_value(mlx->id, 0xFF000000);
			*((int *)(mlx->fog.start + (mlx->wsize.y - px.y - 1) * mlx->fog.lsize) + px.x) = mlx_get_color_value(mlx->id, 0xFF000000);
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
