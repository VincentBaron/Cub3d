/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:38:29 by vincentbaro       #+#    #+#             */
/*   Updated: 2021/01/04 16:09:57 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    create_texture(t_general *mother, t_text *texture)
{ 
    mother->mlx.text.image = mlx_xpm_file_to_image(mother->mlx.ptr, texture->path, &(mother->mlx.text_width), &(mother->mlx.text_height));
    mother->mlx.text.addr = mlx_get_data_addr(mother->mlx.text.image, &(mother->mlx.text.bpp), &(mother->mlx.text.size_line), &(mother->mlx.text.endian));
}

void    wall_position_calculation(t_general *mother)
{
    if (mother->dda.side_pos == 0)
        mother->map.wall_pos = mother->gps.pos.y + mother->dda.perpWallDist * mother->gps.ray.y;
    mother->map.wall_pos -= mother->dda.map.y;
}

void    texture_calculation(t_general *mother)
{
    mother->map.text_pos = (int)(mother->map.wall_pos * (double)(mother->mlx.text_width));

    if (mother->dda.side_pos == 0 && mother->gps.ray.x > 0)
        mother->map.text_pos = mother->mlx.text_width - mother->map.text_pos - 1;
    if (mother->dda.side_pos == 1 && mother->gps.ray.y < 0)
        mother->map.text_pos = mother->mlx.text_width - mother->map.text_pos - 1;
}