#ifndef MLX_HANDLERS_H
# define MLX_HANDLERS_H

int	expose_hook(t_mlx *mlx);
int	motion_hook(int x, int y, t_mlx *mlx);
int	mouse_hook(int button, int x, int y, t_mlx *mlx);
int	key_hook(int key_code, t_mlx *mlx);
int	key_press_hook(int key_code, t_mlx *mlx);
int	key_release_hook(int key_code, t_mlx *mlx);

#endif
