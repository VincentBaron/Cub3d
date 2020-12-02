/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 17:46:54 by vincentbaro       #+#    #+#             */
/*   Updated: 2020/12/02 12:01:05 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void affiliate_texture(t_general *mother, t_text *texture)
{
    if (texture->RGB[0] != -1)
    mother->mlx.img_ray.color = (texture->RGB[0] << 16) + (texture->RGB[1] << 8) + texture->RGB[2];
    else
        mother->mlx.img_ray.color = -1;
}

void    define_wall_color(t_general *mother)
{
    if (mother->args.matrix[mother->dda.map.y][mother->dda.map.x] == '1')
    {
        if (mother->dda.side_pos == 1)
            (mother->gps.ray.y < 0) ? affiliate_texture(mother, &(mother->args.NO)) : affiliate_texture(mother, &(mother->args.SO)); 
        else if (mother->dda.side_pos == 0)
        {
            (mother->gps.ray.x < 0) ? affiliate_texture(mother, &(mother->args.WE)) : affiliate_texture(mother, &(mother->args.EA));
            mother->mlx.img_ray.color /= 2;
        }
        
    }
}