#include "wolf3d.h"
#include <stdio.h>														///debug

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

static t_col	get_height(t_ray ray, double angle, int hside, t_mlx *mlx)
{
	t_col	column;
	t_wld	wld;

	wld = *((t_wld *)mlx->data);
	// column.color = mlx_get_color_value(mlx->id, grid.y * 32 + ((grid.x * 32) << 16));
	if (hside)
	{
		// printf("ray.dist.Y = %f; ray.dist.X = %f\n", ray.dist.y, ray.dist.x);													//debug
		
		if (ray.step.y < 0)
			column.color = mlx_get_color_value(mlx->id, 0x000088);
		else
			column.color = mlx_get_color_value(mlx->id, 0x440088);

		// column.color += mlx_get_color_value(mlx->id, 0x111111);
		if ((int)(0x08 * ray.dist.y) > 0xFF)
			column.fogclr = mlx_get_color_value(mlx->id, 0x000000);
		else
			column.fogclr = mlx_get_color_value(mlx->id, 0 - ((int)(0x08 * ray.dist.y) << 24));
		column.height = ((mlx->wsize.y / 2) / (ray.dist.y * cos(angle) * tan(wld.plr.fov.y / 2)));
	}
	else
	{
		if (ray.step.x < 0)
			column.color = mlx_get_color_value(mlx->id, 0x880000);
		else
			column.color = mlx_get_color_value(mlx->id, 0x880044);

		// printf("ray.dist.x = %f; ray.dist.y = %f\n", ray.dist.x, ray.dist.y);													//debug
		if ((int)(0x08 * ray.dist.x) > 0xFF)
			column.fogclr = mlx_get_color_value(mlx->id, 0x000000);
		else
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
	}
	return (column);

}

t_col	get_column(int col, t_mlx *mlx)
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
	// hside = 0;
	// grid.x -= ray.step.x;
	// grid.y -= ray.step.y;
	// tile = wld.grid[grid.y][grid.x];

	cast(&ray, &grid, wld, "02");
	hside = cast(&ray, &grid, wld, "1");

	ray.dist.x = fabs(ray.dist.x - ray.hyp.x);
	ray.dist.y = fabs(ray.dist.y - ray.hyp.y);

	column = get_height(ray, angle, hside, mlx);
	return (column);
}