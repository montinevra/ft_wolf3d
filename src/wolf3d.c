#include "wolf3d.h"

static t_pos	get_start(char **map)
{
	t_pos	start;
	int		i;
	int		j;

	j = ~0;
	while (map[++j])
	{
		// if (ft_strchr(map[j], '2'))
		// {

		// }
		i = ~0;
		while (map[j][++i])
		{
			if (map[j][i] == '2')
			{
				start.x = i + 0.5;
				start.y = j + 0.5;
				return (start);
			}
		}
	}
	start.x = 0.5;
	start.y = 0.5;
	return (start);
}

void	wolf3d(t_wld wld)
{
	t_mlx		mlx;
	// t_wld		wld;
	// t_player	player;

	mlx.wsize.x = 640 * 2;
	mlx.wsize.y = 400 * 2;
	// wld.map = map;
	wld.plr.pos = get_start(wld.map);
	wld.plr.rot = 0;
	wld.plr.vel.dir = .10;
	wld.plr.vel.mag = .1;
	wld.plr.fov.x = M_TAU / 6;
	wld.plr.fov.y = wld.plr.fov.x * mlx.wsize.y / mlx.wsize.x;
	// wld.plr.fov.y = M_TAU/ 4;//wld.plr.fov.x;// * mlx.wsize.y / mlx.wsize.x;

	// printf("start = %f, %f\n", wld.plr.pos.x, wld.plr.pos.y);								////debug
	// printf("fov = %.30f\n", wld.plr.fov.x);								////debug
	

	// mlx.scalefr = 1.1;
	// init_scale(&mlx);
	// mlx.data = (t_frac *)malloc(sizeof(t_frac));
	// ((t_frac *)mlx.data)->i_max = 0xFF / 8;
	// ((t_frac *)mlx.data)->name = name;
	// ((t_frac *)mlx.data)->c.a = 0;
	// ((t_frac *)mlx.data)->c.b = 0;
	mlx.data = &wld;
	// printf("%f\n", ((t_wld *)mlx.data)->plr.fov.x);									//debug
	mlx_driver(mlx);	

	return ;
}
