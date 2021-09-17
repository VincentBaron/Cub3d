/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:34:46 by vincentbaro       #+#    #+#             */
/*   Updated: 2021/09/17 18:32:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initialise_args(t_input *args)
{
	args->index[0] = "1";
	args->index[1] = "R";
	args->index[2] = "NO";
	args->index[3] = "SO";
	args->index[4] = "WE";
	args->index[5] = "EA";
	args->index[6] = "S";
	args->index[7] = "F";
	args->index[8] = "C";
	args->index[9] = NULL;
	args->F.RGB[0] = -1;
	args->C.RGB[0] = -1;
	args->R[0] = 800;
	args->R[1] = 800;
}

void	init_vars2(t_general *mother)
{
	mother->gps.rot_right = 0;
	mother->gps.event = 0;
	mother->gps.camera.x = 0;
	mother->gps.camera.y = 0;
	mother->gps.ray.x = 0;
	mother->gps.ray.y = 0;
	mother->mlx.img_ray.color = 0;
	mother->mlx.esc = 0;
	mother->mlx.img_map.image = NULL;
	mother->mlx.img_ray.image = NULL;
	mother->mlx.img_sprite.image = NULL;
	mother->mlx.img_map.addr = NULL;
	mother->mlx.img_ray.addr = NULL;
	mother->mlx.img_sprite.addr = NULL;
	mother->args.line = NULL;
	mother->args.map = NULL;
	mother->args.matrix = NULL;
	mother->mlx.ptr = NULL;
	mother->mlx.win = NULL;
	mother->sprite.elem = NULL;
	mother->sprite.zbuffer = NULL;
	mother->sprite.sprite_distance = NULL;
	mother->sprite.sprite_order = NULL;
	mother->mlx.is_created = 0;
}

void	init_vars(t_general *mother)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		mother->args.text[i].img_text.image = NULL;
		mother->args.text[i].path = NULL;
		i++;
	}
	mother->args.r_filled = 1;
	mother->args.c_filled = 0;
	mother->args.f_filled = 0;
	mother->gps.pos.x = 0;
	mother->gps.pos.y = 0;
	mother->gps.dir.x = 0;
	mother->gps.dir.y = 0;
	mother->gps.plane.x = 0;
	mother->gps.plane.y = 0;
	mother->gps.move.x = 0;
	mother->gps.move.y = 0;
	mother->gps.rot_left = 0;
	mother->map_started = 0;
	init_vars2(mother);
}

void	init_map(t_general *mother)
{
	int	map_res;
	int	i;
	int	f;
	int	width;
	int	height;

	map_res = mother->args.R[0] * mother->args.R[1] / 4;
	i = 0;
	width = 0;
	while (mother->args.matrix[i])
	{
		f = 0;
		while (mother->args.matrix[i][f])
			f++;
		if (f > width)
			width = f;
		i++;
	}
	height = i;
	mother->map.size_x = 10;
	mother->map.size_y = 10;
	mother->map.res_x = mother->map.size_x * width;
	mother->map.res_y = mother->map.size_x * height;
}

void	set_background(t_general *mother)
{
	int	x;
	int	y;

	mother->mlx.img_ray.color = (mother->args.C.RGB[0] << 16)
		+ (mother->args.C.RGB[1] << 8) + mother->args.C.RGB[2];
	y = 0;
	while (y < mother->args.R[1])
	{
		x = 0;
		while (x < mother->args.R[0])
		{
			if (y > mother->args.R[1] / 2)
				mother->mlx.img_ray.color = (mother->args.F.RGB[0] << 16)
					+ (mother->args.F.RGB[1] << 8) + mother->args.F.RGB[2];
			draw_pixel(&(mother->mlx.img_ray), x, y);
			x++;
		}
		y++;
	}
}
