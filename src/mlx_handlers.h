/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_handlers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 16:41:33 by pvan-erp          #+#    #+#             */
/*   Updated: 2017/05/07 16:41:38 by pvan-erp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_HANDLERS_H
# define MLX_HANDLERS_H

int	expose_hook(t_mlx *mlx);
int	exit_hook(t_mlx *mlx);
int	loop_hook(t_mlx *mlx);
int	motion_hook(int x, int y, t_mlx *mlx);
int	mouse_hook(int button, int x, int y, t_mlx *mlx);
int	key_hook(int key_code, t_mlx *mlx);
int	key_press_hook(int key_code, t_mlx *mlx);
int	key_release_hook(int key_code, t_mlx *mlx);

#endif
