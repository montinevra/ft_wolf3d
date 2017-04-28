#ifndef MLX_DRIVER_H
# define MLX_DRIVER_H
# include <stdlib.h>
# include <pthread.h>
# include "../minilibx_macos/mlx.h"
# define THREADS 4

// typedef struct	s_px
// {
// 	int	x;
// 	int	y;
// 	int	clr;
// }				t_px;

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

// typedef struct	s_offset
// {
// 	long double	a;
// 	long double	b;
// }				t_offset;

typedef struct	s_mlx_img
{
	void	*id;
	char	*start;
	int		bppx;
	int		lsize;
	int		endian;
}				t_mlx_img;

typedef	struct	s_mlx
{
	void		*id;
	void		*win;
	t_mlx_img	img;
	t_coord		wsize;
	// t_offset	offset;
 	// long double	scale;
	// float		scalefr;
	void		*data;
}				t_mlx;

typedef struct	s_mlx_thread
{
	t_mlx	*mlx;
	int		y;	
}				t_mlx_thread;

void			draw(t_mlx *mlx);

#endif
