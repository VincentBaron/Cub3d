/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:27:55 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/14 23:05:57 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	texture_orientation(t_general *mother)
{
	wall_position_calculation(mother);
	if (mother->dda.side_pos == 1 && mother->gps.ray.y < 0)
		return (0);
	if (mother->dda.side_pos == 1 && mother->gps.ray.y > 0)
		return (1);
	if (mother->dda.side_pos == 0 && mother->gps.ray.x > 0)
		return (2);
	if (mother->dda.side_pos == 0 && mother->gps.ray.x < 0)
		return (3);
	return (0);
}

void	draw_line(t_general *mother)
{
	int		y;
	double	text_pos;
	int		text_y;
	int		text_index;
	double	step;

	text_index = texture_orientation(mother);
	texture_calculation(mother, text_index);
	y = mother->dda.line_start;
	step = 1.0 * mother->args.text[text_index].text_height
		/ mother->dda.wall_height;
	text_pos = (mother->dda.line_start - mother->args.R[1]
			/ 2 + mother->dda.wall_height / 2) * step;
	while (y < mother->dda.line_end)
	{
		text_y = (int)text_pos
			& (mother->args.text[text_index].text_height - 1);
		text_pos += step;
		mother->mlx.img_ray.color = *(unsigned int *)
			(mother->args.text[text_index].img_text.addr + mother->args.text
			[text_index].img_text.size_line * text_y + mother->map.text_pos
				* mother->args.text[text_index].img_text.bpp / 8);
		draw_pixel(&(mother->mlx.img_ray), mother->mlx.slice, y);
		y++;
	}
}

void	draw_wall(t_general *mother)
{
	mother->dda.wall_height = (int)(mother->args.R[1]
			/ mother->dda.perpWallDist);
	mother->dda.line_start = -(mother->dda.wall_height)
		/ 2 + mother->args.R[1] / 2;
	if (mother->dda.line_start < 0)
		mother->dda.line_start = 0;
	mother->dda.line_end = mother->dda.wall_height
		/ 2 + mother->args.R[1] / 2;
	if (mother->dda.line_end >= mother->args.R[1])
		mother->dda.line_end = mother->args.R[1] - 1;
	draw_line(mother);
}

void	raycasting(t_general *mother)
{
	mother->mlx.slice = 0;
	while (mother->mlx.slice < mother->args.R[0])
	{
		mother->gps.camera.x = 2 * mother->mlx.slice
			/ (double)(mother->args.R[0]) - 1;
		mother->gps.ray.x = mother->gps.dir.x
			+ mother->gps.camera.x * mother->gps.plane.x;
		mother->gps.ray.y = mother->gps.dir.y
			+ mother->gps.camera.x * mother->gps.plane.y;
		distance_calculations(mother);
		draw_wall(mother);
		mother->sprite.zbuffer[mother->mlx.slice]
			= mother->dda.perpWallDist;
		(mother->mlx.slice)++;
	}
	sort_sprites(mother);
	sprite_projection(mother);
}
