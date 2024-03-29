/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:51:16 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/15 11:05:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	find_direction2(t_general *mother)
{
	if (mother->args.matrix[(int)(mother->gps.pos.y)]
		[(int)(mother->gps.pos.x)] == 'E')
	{
		mother->gps.dir.x = 1.00;
		mother->gps.dir.y = 0.00;
		mother->gps.plane.x = 0.00;
		mother->gps.plane.y = 0.66;
	}
	if (mother->args.matrix[(int)(mother->gps.pos.y)]
		[(int)(mother->gps.pos.x)] == 'W')
	{
		mother->gps.dir.x = -1.00;
		mother->gps.dir.y = 0.00;
		mother->gps.plane.x = 0.00;
		mother->gps.plane.y = -0.66;
	}
}

void	find_direction(t_general *mother)
{
	if (mother->args.matrix[(int)(mother->gps.pos.y)]
		[(int)(mother->gps.pos.x)] == 'N')
	{
		mother->gps.dir.x = 0.00;
		mother->gps.dir.y = -1.01;
		mother->gps.plane.x = 0.66;
		mother->gps.plane.y = 0.00;
	}
	if (mother->args.matrix[(int)(mother->gps.pos.y)]
		[(int)(mother->gps.pos.x)] == 'S')
	{
		mother->gps.dir.x = 0.00;
		mother->gps.dir.y = 1.00;
		mother->gps.plane.x = -0.66;
		mother->gps.plane.y = 0.00;
	}
	find_direction2(mother);
}

void	position_info(t_general *mother)
{
	int		i;
	int		f;
	char	pos;

	mother->gps.pos.y = -1;
	mother->gps.pos.x = -1;
	i = -1;
	while (mother->args.matrix[++i])
	{
		f = 0;
		while (mother->args.matrix[i][f])
		{
			pos = mother->args.matrix[i][f];
			if (pos == 'N' || pos == 'S' || pos == 'E' || pos == 'W')
			{
				mother->gps.pos.x = f + 0.5;
				mother->gps.pos.y = i + 0.5;
				break ;
			}
			f++;
		}
	}
	find_direction(mother);
	mother->args.matrix[(int)(mother->gps.pos.y)]
	[(int)(mother->gps.pos.x)] = '0';
}
