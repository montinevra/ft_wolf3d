#include "mlx_driver.h"
#include "mlx_handlers.h"
#include "wolf3d.h"														//debuf

static int	is_big_endian(void)
{
	const unsigned int	end = 1;

	return (*(((char *)&end) + 3));
}

void		mlx_driver(t_mlx mlx)
{
	char	*wname;

	wname = ft_strjoin("Wolf3D - ", ((t_wld *)mlx.data)->name);
	mlx.id = mlx_init();
	mlx.win = mlx_new_window(mlx.id, mlx.wsize.x, mlx.wsize.y, wname);
	ft_strdel(&wname);
	mlx.img.id = mlx_new_image(mlx.id, mlx.wsize.x, mlx.wsize.y);
	mlx.img.bppx = 32;
	mlx.img.lsize = mlx.wsize.y * mlx.img.bppx / 4;
	mlx.img.endian = is_big_endian();
	mlx.img.start = mlx_get_data_addr(mlx.img.id, &mlx.img.bppx, &mlx.img.lsize,
		&mlx.img.endian);
	// int i = 0;
	// while (1)
	// {
	// 	printf("image lenght = %d img[i] = %c\n", i, mlx.img.start[i]);										//////debug
	// 	i++;
	// }
	mlx_mouse_hook(mlx.win, mouse_hook, &mlx);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_expose_hook(mlx.win, expose_hook, &mlx);
	mlx_hook(mlx.win, 2, 0, key_press_hook, &mlx);
	// mlx_hook(mlx.win, 3, 0, key_release_hook, &mlx);
	// if (ft_strequ(((t_frac *)mlx.data)->name, "julia"))
	// mlx_hook(mlx.win, 6, 0, motion_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	// mlx_do_key_autorepeatoff(mlx.id);

	mlx_loop_hook(mlx.id, loop_hook, &mlx);
	mlx_loop(mlx.id);
}
