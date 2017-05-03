#include "wolf3d.h"
#include <stdio.h>																							///debug

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

int			key_hook(int key_code, t_mlx *mlx)
{
	if (key_code == 53)
	{
		mlx_destroy_window(mlx->id, mlx->win);
		mlx_destroy_image(mlx->id, mlx->img.id);
		free(mlx->id);
		ft_arrldel((void **)((t_wld *)(mlx->data))->map, ((t_wld *)mlx->data)->size.y);
		exit(0);
	}

	// printf("key = %d\n", key_code);																		////debug
	return (0);
}


int			key_press_hook(int key_code, t_mlx *mlx)
{

	if (key_code >= 0 && key_code <= MAXKEYS)
	{
		// printf("key pressed!\n");
		mlx->keys[key_code] = 1;
	}
	// printf("key = %d\n", key_code);																		////debug

	return (0);
}

int			key_release_hook(int key_code, t_mlx *mlx)
{
	if (key_code >= 0 && key_code <= MAXKEYS)
	{
		// printf("key reelased!\n");
		mlx->keys[key_code] = 0;
	}
	if (key_code == 53)
	{
		mlx_destroy_window(mlx->id, mlx->win);
		mlx_destroy_image(mlx->id, mlx->img.id);
		free(mlx->id);
		ft_arrldel((void **)((t_wld *)(mlx->data))->map, ((t_wld *)mlx->data)->size.y);
		exit(0);
	}
	// printf("key = %d\n", key_code);																		////debug
	return (0);
}

