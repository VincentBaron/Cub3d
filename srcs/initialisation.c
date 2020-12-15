/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:34:46 by vincentbaro       #+#    #+#             */
/*   Updated: 2020/12/15 22:06:45 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    init_vars(t_general *mother)
{
    mother->gps.pos.x = 0;
    mother->gps.pos.y = 0;
    mother->gps.dir.x = 0;
    mother->gps.dir.y = 0;
    mother->gps.plane.x = 0;
    mother->gps.plane.y = 0;
    mother->gps.move.x = 0;
    mother->gps.move.y = 0;
    mother->gps.rot_left = 0;
    mother->gps.rot_right = 0;
    mother->gps.event = 0;
    mother->gps.camera.x = 0;
    mother->gps.camera.y = 0;
    mother->gps.ray.x = 0;
    mother->gps.ray.y = 0;
    mother->mlx.img_ray.color = 0;
    mother->mlx.esc = 0;
    //mother->texture.flag = 0;
}

void    init_map(t_general *mother)
{
    int map_res;
    int i;
    int f;
    int width;
    int height;

    map_res = mother->args.R[0] * mother->args.R[1] / 4;

    i = 0;
    while (mother->args.matrix[i])
    {
        f = 0;
        while (mother->args.matrix[i][f])
            f++;
        if (f > width)
            width = f;
        i++;
    }
    height = i;
    mother->map.size_x = 10;
    mother->map.size_y = 10;
    mother->map.res_x = mother->map.size_x * width;
    mother->map.res_y = mother->map.size_x * height;
}

void    set_background(t_general *mother)
{
    int x;
    int y;

    affiliate_texture(&(mother->mlx.img_ray), &(mother->args.C));
    y = 0;
    while (y <= mother->args.R[1])
    {
        x = 0;
        while (x <= mother->args.R[0])
        {
            if (y > mother->args.R[1] / 2)
                affiliate_texture(&(mother->mlx.img_ray), &(mother->args.F));
            draw_pixel(&(mother->mlx.img_ray), x, y);
            x++;
        }
        y++;
    }
}