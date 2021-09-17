/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:37:04 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/17 22:57:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sprite_distance(t_general *mother, int i)
{
	mother->sprite.pos.x = mother->sprite.elem[i].x
		- mother->gps.pos.x + 0.5;
	mother->sprite.pos.y = mother->sprite.elem[i].y
		- mother->gps.pos.y + 0.5;
	mother->sprite.inv_det = 1.0 / (mother->gps.plane.x
			* mother->gps.dir.y - mother->gps.dir.x * mother->gps.plane.y);
	mother->sprite.transform.x = mother->sprite.inv_det
		* (mother->gps.dir.y * mother->sprite.pos.x - mother->gps.dir.x
			* mother->sprite.pos.y);
	mother->sprite.transform.y = mother->sprite.inv_det
		* (-mother->gps.plane.y * mother->sprite.pos.x + mother->gps.plane.x
			* mother->sprite.pos.y);
	mother->sprite.spritescreen = (int)((mother->args.r[0] / 2)
			* (1 + mother->sprite.transform.x / mother->sprite.transform.y));
	mother->sprite.sprite_height = abs((int)(mother->args.r[1]
				/ (mother->sprite.transform.y)));
	mother->sprite.sprite_width = abs((int)(mother->args.r[1]
				/ (mother->sprite.transform.y)));
}

void	drawing_constrains(t_general *mother)
{
	mother->sprite.draw_start.y = -mother->sprite.sprite_height
		/ 2 + mother->args.r[1] / 2;
	if (mother->sprite.draw_start.y < 0)
		mother->sprite.draw_start.y = 0;
	mother->sprite.draw_end.y = mother->sprite.sprite_height
		/ 2 + mother->args.r[1] / 2;
	if (mother->sprite.draw_end.y >= mother->args.r[1])
		mother->sprite.draw_end.y = mother->args.r[1] - 1;
	mother->sprite.draw_start.x = -mother->sprite.sprite_width
		/ 2 + mother->sprite.spritescreen;
	if (mother->sprite.draw_start.x < 0)
		mother->sprite.draw_start.x = 0;
	mother->sprite.draw_end.x = mother->sprite.sprite_width
		/ 2 + mother->sprite.spritescreen;
	if (mother->sprite.draw_end.x >= mother->args.r[0])
		mother->sprite.draw_end.x = mother->args.r[0] - 1;
}

static void	sprite_display(t_general *mother, int j, int stripe)
{
	int	d;
	int	txtr_y;

	d = j * 256 - mother->args.r[1] * 128 + mother->sprite.sprite_height * 128;
	txtr_y = ((d * mother->args.text[4].text_height)
			/ mother->sprite.sprite_height) / 256;
	mother->mlx.img_ray.color = *(unsigned int *)
		(mother->args.text[4].img_text.addr
			+ mother->args.text[4].img_text.size_line
			* txtr_y + mother->sprite.tex.x
			* (mother->args.text[4].img_text.bpp / 8));
	if ((mother->mlx.img_ray.color & 0x00FFFFFF) != 0)
		draw_pixel(&(mother->mlx.img_ray), stripe, j);
}

void	sprite_projection2(t_general *mother, int stripe)
{
	int	j;

	mother->sprite.tex.x = (int)(256 * (stripe - (-mother->sprite.sprite_width
					/ 2 + mother->sprite.spritescreen))
			* mother->args.text[4].text_width
			/ mother->sprite.sprite_width) / 256;
	if (mother->sprite.transform.y > 0 && stripe
		> 0 && stripe < mother->args.r[0]
		&& mother->sprite.transform.y < mother->sprite.zbuffer[stripe])
	{
		j = mother->sprite.draw_start.y;
		while (j < mother->sprite.draw_end.y)
		{
			sprite_display(mother, j, stripe);
			++j;
		}
	}
}

void	sprite_projection(t_general *mother)
{
	int	i;
	int	stripe;

	i = 0;
	while (i < mother->sprite.sprite_count)
	{
		sprite_distance(mother, i);
		drawing_constrains(mother);
		stripe = mother->sprite.draw_start.x;
		while (stripe < mother->sprite.draw_end.x)
		{	
			sprite_projection2(mother, stripe);
			stripe++;
		}
		i++;
	}
}
