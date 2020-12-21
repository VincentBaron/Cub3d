/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:38:29 by vincentbaro       #+#    #+#             */
/*   Updated: 2020/12/21 17:35:31 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    create_texture(t_general *mother, t_text *texture)
{
    int width;
    int height;
    
    mother->mlx.text.image = mlx_xpm_file_to_image(mother->mlx.ptr, texture->path, &width, &height);
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
    int text_width;

    text_width = 1;
    mother->map.text_pos = (int)(mother->map.wall_pos * (double)(text_width));

    if (mother->dda.side_pos == 0 && mother->gps.ray.x > 0)
        mother->map.text_pos = text_width - mother->map.text_pos - 1;
    if (mother->dda.side_pos == 1 && mother->gps.ray.y < 0)
        mother->map.text_pos = text_width - mother->map.text_pos - 1;
}

void    define_texture_color(t_general *mother)
{
    wall_position_calculation(mother);
    texture_calculation(mother);
}