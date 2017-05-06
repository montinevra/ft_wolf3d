#include "mlx_driver.h"
#include "mlx_handlers.h"
#include "wolf3d.h"														//debuf

static int			is_big_endian(void)
{
	const unsigned int	end = 1;

	return (*(((char *)&end) + 3));
}

// static void			bg_init(t_mlx_img *img, t_mlx mlx)
// {
// 	int	i;

// 	i = ~0;
// 	while (++i < mlx.wsize.x * mlx.wsize.y)
// 	{
// 		img->start[i] = mlx_get_color_value(mlx.id, 0x777777);
// 	}
// }

static t_mlx_img	img_init(t_mlx mlx)
{
	t_mlx_img	img;

	img.id = mlx_new_image(mlx.id, mlx.wsize.x, mlx.wsize.y);
	img.bppx = 32;
	img.lsize = mlx.wsize.y * img.bppx / 4;
	img.endian = is_big_endian();
	img.start = mlx_get_data_addr(img.id, &img.bppx, &img.lsize,
		&img.endian);
	return (img);
}

void				mlx_driver(t_mlx mlx)
{
	char	*wname;
	int 	i;

	wname = ft_strjoin("Wolf3D - ", ((t_wld *)mlx.data)->name);
	mlx.id = mlx_init();
	mlx.win = mlx_new_window(mlx.id, mlx.wsize.x, mlx.wsize.y, wname);
	ft_strdel(&wname);
	mlx.img = img_init(mlx);
	mlx.fog = img_init(mlx);
	// mlx.bg = img_init(mlx);
	// bg_init(&mlx.bg, mlx);
	i = ~0;
	while (++i < MAXKEYS)
		mlx.keys[i] = 0;
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
	mlx_hook(mlx.win, 3, 0, key_release_hook, &mlx);
	// mlx_hook(mlx.win, 6, 0, motion_hook, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_hook, &mlx);
	mlx_do_key_autorepeatoff(mlx.id);

	mlx_loop_hook(mlx.id, loop_hook, &mlx);
	mlx_loop(mlx.id);
}
