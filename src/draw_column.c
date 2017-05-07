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

static unsigned int	get_fogclr(float dist, t_mlx *mlx)
{
	unsigned int	fogclr;

	if ((int)(0x08 * dist) > 0xFF)
		fogclr = mlx_get_color_value(mlx->id, 0x000000);
	else
		fogclr = mlx_get_color_value(mlx->id, 0 - ((int)(0x08 * dist) << 24));
	return (fogclr);
}

static t_col	get_col_attr(t_ray ray, double angle, int hside, t_mlx *mlx)
{
	t_col	column;

	if (hside)
	{
		if (ray.step.y < 0)
			column.color = mlx_get_color_value(mlx->id, 0x000088);
		else
			column.color = mlx_get_color_value(mlx->id, 0x440088);
		column.fogclr = get_fogclr(ray.dist.y, mlx);
		column.height = ((mlx->wsize.y / 2) / (ray.dist.y * cos(angle) * 
				tan(((t_wld *)mlx->data)->plr.fov.y / 2)));
	}
	else
	{
		if (ray.step.x < 0)
			column.color = mlx_get_color_value(mlx->id, 0x880000);
		else
			column.color = mlx_get_color_value(mlx->id, 0x880044);
		column.fogclr = get_fogclr(ray.dist.x, mlx);
		column.height = ((mlx->wsize.y / 2) / (ray.dist.x * cos(angle) * 
				tan(((t_wld *)mlx->data)->plr.fov.y / 2)));
	}
	if (column.height > mlx->wsize.y / 2)
		column.height = mlx->wsize.y / 2;
	return (column);
}

t_col	get_column(int col, t_mlx *mlx)
{
	t_col	column;
	double	angle;
	t_wld	wld;
	t_ray	ray;
	t_coord	grid;
	int 	hside;

	wld = *((t_wld *)mlx->data);
	angle = atan2(col - mlx->wsize.x / 2, mlx->wsize.x / tan(wld.plr.fov.x / 2));
	ray.hyp.x = 1.0 / cos(angle + wld.plr.rot);
	ray.hyp.y = 1.0 / sin(angle + wld.plr.rot);
	grid.x = floor(wld.plr.pos.x);
	grid.y = floor(wld.plr.pos.y);
	ray = ray_start(ray, grid, wld);
	cast(&ray, &grid, wld, "02");
	hside = cast(&ray, &grid, wld, "1");
	ray.dist.x = fabs(ray.dist.x - ray.hyp.x);
	ray.dist.y = fabs(ray.dist.y - ray.hyp.y);
	column = get_col_attr(ray, angle, hside, mlx);
	return (column);
}