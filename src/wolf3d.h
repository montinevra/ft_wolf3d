#ifndef WOLF3D_H
# define WOLF3D_H
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "more_math.h"
# include "mlx_driver.h"

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

typedef	struct	s_plr
{
	t_pos	pos;
	t_pos	fov;
	t_vec	vel;
	double	rot;
}				t_plr;

typedef struct	s_wld
{
	char		**map;
	char		*name;
	t_coord		size;
	t_plr		plr;
}				t_wld;

typedef struct	s_ray
{
	t_pos	hyp;
	t_pos	dist;
	t_coord	step;	
}				t_ray;

typedef struct	s_col
{
	int	height;
	int	color;
	int	fogclr;
}				t_col;

t_wld	loadmap(int fd);
void	wolf3d(t_wld wld);
void	mlx_driver(t_mlx mlx);
t_col	get_column(int col, t_mlx *mlx);

#endif