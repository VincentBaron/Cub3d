/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:49:29 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/17 19:17:08 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_general *mother)
{
	mother->gps.event = 1;
	if (keycode == UP)
		mother->gps.move.y = -1;
	else if (keycode == DOWN)
		mother->gps.move.y = 1;
	else if (keycode == LEFT)
		mother->gps.move.x = -1;
	else if (keycode == RIGHT)
		mother->gps.move.x = 1;
	else if (keycode == ROT_LEFT)
		mother->gps.rot_left = 1;
	else if (keycode == ROT_RIGHT)
		mother->gps.rot_right = 1;
	else if (keycode == ESC)
		ft_clean(mother);
	return (0);
}

int	key_release(int keycode, t_general *mother)
{
	if (keycode == UP)
		mother->gps.move.y = 0;
	else if (keycode == DOWN)
		mother->gps.move.y = 0;
	else if (keycode == LEFT)
		mother->gps.move.x = 0;
	else if (keycode == RIGHT)
		mother->gps.move.x = 0;
	else if (keycode == ROT_LEFT)
		mother->gps.rot_left = 0;
	else if (keycode == ROT_RIGHT)
		mother->gps.rot_right = 0;
	return (0);
}

int	events_list(t_general *mother)
{
	if (mother->mlx.esc == 0)
	{
		set_background(mother);
		movement(mother);
		raycasting(mother);
		display_images(mother);
	}
	return (0);
}

void	game_start(t_general *mother)
{
	if (mother->mlx.is_created == 0)
	{
		mother->mlx.win = mlx_new_window(mother->mlx.ptr,
				mother->args.R[0], mother->args.R[1], "Cub3d");
		if (!(mother->mlx.win))
			error(mother, 6);
		mother->mlx.is_created = 1;
	}
	create_images(mother);
	mlx_hook(mother->mlx.win, KEY_PRESS, 1L << 0, &key_press, mother);
	mlx_hook(mother->mlx.win, 33, (1L << 17), ft_clean, mother);
	mlx_hook(mother->mlx.win, KEY_RELEASE, 1L << 1, &key_release, mother);
	mlx_loop_hook(mother->mlx.ptr, &events_list, mother);
	mlx_loop(mother->mlx.ptr);
}
