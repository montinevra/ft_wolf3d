#ifndef WOLF3D_H
# define WOLF3D_H
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "more_math.h"
# include "mlx_driver.h"
#include <stdio.h>															//debug

// # define M_TAU M_PI * 2.0 
// # define MAXKEYS 279

// typedef struct	s_point
// {
// 	int	x;
// 	int	y;
// }				t_point;

// typedef struct	s_map
// {
// 	char	**map;
// 	t_point	start;
// }				t_map;

typedef struct	s_pos
{
	double	x;
	double	y;
}				t_pos;

// typedef struct	s_vel
// {
// 	double	mag;
// 	double	dir;
// }				t_vel;

typedef	struct	s_plr
{
	t_pos	pos;
	t_pos	fov;
	t_vec	vel;
	double	rot;
}				t_plr;

// typedef struct	s_keys
// {
	
// };

typedef struct	s_wld
{
	char		**map;
	char		*name;
	t_coord		size;
	t_plr		plr;
	// int			keys[MAXKEYS];
}				t_wld;

typedef struct	s_col
{
	int	height;
	int	color;
}				t_col;

t_wld	loadmap(int fd);
void	wolf3d(t_wld wld);
void	mlx_driver(t_mlx mlx);

#endif