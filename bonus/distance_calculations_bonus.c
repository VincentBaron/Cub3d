/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:07:46 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/08 10:46:50 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	initial_side_distance(t_general *mother)
{
	if (mother->gps.ray.x < 0)
	{
		mother->dda.step.x = -1;
		mother->dda.side.x = (mother->gps.pos.x
				- mother->dda.map.x) * mother->dda.delta.x;
	}
	else
	{
		mother->dda.step.x = 1;
		mother->dda.side.x = (mother->dda.map.x + 1.0
				- mother->gps.pos.x) * mother->dda.delta.x;
	}
	if (mother->gps.ray.y < 0)
	{
		mother->dda.step.y = -1;
		mother->dda.side.y = (mother->gps.pos.y
				- mother->dda.map.y) * mother->dda.delta.y;
	}
	else
	{
		mother->dda.step.y = 1;
		mother->dda.side.y = (mother->dda.map.y + 1.0
				- mother->gps.pos.y) * mother->dda.delta.y;
	}
}

void	collision_calculator(t_general *mother)
{
	while (mother->dda.hit == 0)
	{
		if (mother->dda.side.x < mother->dda.side.y)
		{
			mother->dda.side.x += mother->dda.delta.x;
			mother->dda.map.x += mother->dda.step.x;
			mother->dda.side_pos = 0;
		}
		else
		{
			mother->dda.side.y += mother->dda.delta.y;
			mother->dda.map.y += mother->dda.step.y;
			mother->dda.side_pos = 1;
		}
		if (mother->args.matrix[mother->dda.map.y][mother->dda.map.x] == '1')
			mother->dda.hit = 1;
	}
}

void	distance_calculations(t_general *mother)
{
	mother->dda.map.x = (int)mother->gps.pos.x;
	mother->dda.map.y = (int)mother->gps.pos.y;
	mother->dda.delta.x = fabs(1 / mother->gps.ray.x);
	mother->dda.delta.y = fabs(1 / mother->gps.ray.y);
	mother->dda.hit = 0;
	initial_side_distance(mother);
	collision_calculator(mother);
	if (mother->dda.side_pos == 0)
		mother->dda.perpWallDist = (mother->dda.map.x - mother->gps.pos.x
				+ (1 - mother->dda.step.x) / 2) / mother->gps.ray.x;
	else
		mother->dda.perpWallDist = (mother->dda.map.y - mother->gps.pos.y
				+ (1 - mother->dda.step.y) / 2) / mother->gps.ray.y;
}
