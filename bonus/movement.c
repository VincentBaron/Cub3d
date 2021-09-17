/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:51:22 by user42            #+#    #+#             */
/*   Updated: 2021/09/14 23:05:23 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	movement4(t_general *mother, double *old_dir_x, double *old_plane_x)
{
	if (mother->gps.rot_right == 1)
	{
		*old_dir_x = mother->gps.dir.x;
		mother->gps.dir.x = mother->gps.dir.x * cosf(ROT_SPEED)
			- mother->gps.dir.y * sinf(ROT_SPEED);
		mother->gps.dir.y = *old_dir_x * sinf(ROT_SPEED) + mother->gps.dir.y
			* cosf(ROT_SPEED);
		*old_plane_x = mother->gps.plane.x;
		mother->gps.plane.x = mother->gps.plane.x * cosf(ROT_SPEED)
			- mother->gps.plane.y * sinf(ROT_SPEED);
		mother->gps.plane.y = *old_plane_x * sinf(ROT_SPEED)
			+ mother->gps.plane.y * cosf(ROT_SPEED);
	}
}

void	movement2(t_general *mother, double *old_dir_x, double *old_plane_x)
{
	if (mother->gps.rot_left == 1)
	{
		*old_dir_x = mother->gps.dir.x;
		mother->gps.dir.x = mother->gps.dir.x * cosf(-ROT_SPEED)
			- mother->gps.dir.y * sinf(-ROT_SPEED);
		mother->gps.dir.y = *old_dir_x * sinf(-ROT_SPEED) + mother->gps.dir.y
			* cosf(-ROT_SPEED);
		*old_plane_x = mother->gps.plane.x;
		mother->gps.plane.x = mother->gps.plane.x * cosf(-ROT_SPEED)
			- mother->gps.plane.y * sinf(-ROT_SPEED);
		mother->gps.plane.y = *old_plane_x * sinf(-ROT_SPEED)
			+ mother->gps.plane.y * cosf(-ROT_SPEED);
	}
	movement4(mother, old_dir_x, old_plane_x);
}

void	movement3(t_general *mother)
{
	if (mother->gps.move.x == -1)
	{
		if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)
			(mother->gps.pos.x - mother->gps.plane.x * MOVE_SPEED)] == '0')
			mother->gps.pos.x -= mother->gps.plane.x * MOVE_SPEED;
		if (mother->args.matrix[(int)(mother->gps.pos.y - mother->gps.plane.y
				* MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
			mother->gps.pos.y -= mother->gps.plane.y * MOVE_SPEED;
	}
	if (mother->gps.move.x == 1)
	{
		if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)
			(mother->gps.pos.x + mother->gps.plane.x * MOVE_SPEED)] == '0')
			mother->gps.pos.x += mother->gps.plane.x * MOVE_SPEED;
		if (mother->args.matrix[(int)(mother->gps.pos.y + mother->gps.plane.y
				* MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
			mother->gps.pos.y += mother->gps.plane.y * MOVE_SPEED;
	}
}

void	movement(t_general *mother)
{
	double	old_dir_x;
	double	old_plane_x;

	if (mother->gps.move.y == -1)
	{
		if (mother->args.matrix[(int)(mother->gps.pos.y + mother->gps.dir.y
				* MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
			mother->gps.pos.y += mother->gps.dir.y * MOVE_SPEED;
		if (mother->args.matrix[(int)(mother->gps.pos.y)]
			[(int)(mother->gps.pos.x + mother->gps.dir.x * MOVE_SPEED)] == '0')
			mother->gps.pos.x += mother->gps.dir.x * MOVE_SPEED;
	}
	if (mother->gps.move.y == 1)
	{
		if (mother->args.matrix[(int)(mother->gps.pos.y)]
		[(int)(mother->gps.pos.x - mother->gps.dir.x * MOVE_SPEED)] == '0')
			mother->gps.pos.x -= mother->gps.dir.x * MOVE_SPEED;
		if (mother->args.matrix[(int)(mother->gps.pos.y - mother->gps.dir.y
				* MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
			mother->gps.pos.y -= mother->gps.dir.y * MOVE_SPEED;
	}
	movement2(mother, &old_dir_x, &old_plane_x);
	movement3(mother);
}
