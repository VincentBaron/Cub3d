/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:27:55 by vbaron            #+#    #+#             */
/*   Updated: 2020/11/10 11:13:09 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void    set_texture(t_general *mother)
{
    if (horizontal_intersection_calculation(mother) == vertical_intersection_calculation(mother))
        mother->mlx.img_ray.color = (0 << 16) + (204 << 8) + 102;
    else
        mother->mlx.img_ray.color = (153 << 16) + (0 << 8) + 0;
    
}

void    draw_slice(t_general *mother, float slice)
{
    float slice_height;
    int y;

    slice_height = (1 / mother->raycast.dist_inter) * mother->raycast.dist_projection;

    y = (mother->args.R[1] - slice_height) / 2;
    set_texture(mother);
    while (y < slice_height)
    {
        draw_pixel(&(mother->mlx.img_ray), slice, y);
        y++;
    }
}

void    draw_rays(t_general *mother)
{
    //float angle_offset;

   // angle_offset = 1.0472 / mother->args.R[0];
    //mother->raycast.angle = mother->gps.angle + 0.523599;
    //while (mother->raycast.angle > 0)
    {
        check_intersection(mother);
        //draw_slice(mother, slice);
        //draw_map_ray(mother);
       // mother->raycast.angle -= angle_offset;
    }

}