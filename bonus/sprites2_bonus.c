/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 10:55:58 by user42            #+#    #+#             */
/*   Updated: 2021/09/17 19:14:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	part3(t_general *mother)
{
	mother->sprite.zbuffer = (int *)malloc(sizeof(int) * mother->args.R[0]);
	if (!mother->sprite.zbuffer)
		error(mother, 3);
	mother->sprite.sprite_order = (int *)malloc(sizeof(int)
			* mother->sprite.sprite_count);
	if (!mother->sprite.sprite_order)
		error(mother, 3);
	mother->sprite.sprite_distance = (int *)malloc(sizeof(int)
			* mother->sprite.sprite_count);
	if (!mother->sprite.sprite_distance)
		error(mother, 3);
}

void	part2(t_general *mother)
{
	int	z;
	int	i;
	int	f;

	mother->sprite.elem = (t_coor *)malloc(sizeof(t_coor)
			* (mother->sprite.sprite_count + 1));
	if (!mother->sprite.elem)
		error(mother, 3);
	i = 0;
	z = 0;
	while (mother->args.matrix[i])
	{
		f = -1;
		while (mother->args.matrix[i][++f])
		{
			if (mother->args.matrix[i][f] == '2')
			{
				mother->sprite.elem[z].x = f;
				mother->sprite.elem[z].y = i;
				z++;
			}
		}
		i++;
	}
	mother->sprite.elem[z].x = -1;
}

void	create_sprites(t_general *mother)
{
	int	i;
	int	f;

	i = 0;
	mother->sprite.sprite_count = 0;
	while (mother->args.matrix[i])
	{
		f = 0;
		while (mother->args.matrix[i][f])
		{
			if (mother->args.matrix[i][f] == '2')
				mother->sprite.sprite_count++;
			f++;
		}
		i++;
	}
	part2(mother);
	part3(mother);
}

void	sort_sprites(t_general *mother)
{
	int			i;
	t_coor		dist;
	t_double	pos;
	t_coor		temp;

	i = 0;
	while (i + 1 < mother->sprite.sprite_count)
	{
		pos = mother->gps.pos;
		dist.x = ((pos.x - mother->sprite.elem[i].x) * (pos.x
					- mother->sprite.elem[i].x) + (pos.y - mother->sprite.elem
				[i].y) * (pos.y - mother->sprite.elem[i].y));
		dist.y = ((pos.x - mother->sprite.elem[i + 1].x) * (pos.x
					- mother->sprite.elem[i + 1].x) + (pos.y - mother->sprite
					.elem[i + 1].y) * (pos.y - mother->sprite.elem[i + 1].y));
		if (dist.x < dist.y)
		{
			temp = mother->sprite.elem[i];
			mother->sprite.elem[i] = mother->sprite.elem[i + 1];
			mother->sprite.elem[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}
