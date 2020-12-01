/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starting_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 14:51:16 by vbaron            #+#    #+#             */
/*   Updated: 2020/12/01 18:48:01 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    find_direction(t_general *mother)
{
    if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x)] == 'N')
    {
        mother->gps.dir.x = 0;
        mother->gps.dir.y = -1;
        mother->gps.plane.x = 0.66;
        mother->gps.plane.y = 0;

    }
    if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x)] == 'S')
    {
        mother->gps.dir.x = 0;
        mother->gps.dir.y = 1;
        mother->gps.plane.x = -0.66;
        mother->gps.plane.y = 0;
    }
    if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x)] == 'E')
    {
        mother->gps.dir.x = 1;
        mother->gps.dir.y = 0;
        mother->gps.plane.x = 0;
        mother->gps.plane.y = 0.66;
    }
    if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x)] == 'W')
    {
        mother->gps.dir.x = -1;
        mother->gps.dir.y = 0;
        mother->gps.plane.x = 0;
        mother->gps.plane.y = -0.66;
    }
}

void    position_info(t_general *mother)
{
    int i;
    int f;
    
    mother->gps.pos.y = -1;
    mother->gps.pos.x = -1;
    i = 0;
    while (mother->args.matrix[i])
    {
        f = 0;
        while (mother->args.matrix[i][f])
        {
            if (mother->args.matrix[i][f] == 'N' || mother->args.matrix[i][f] == 'S' || mother->args.matrix[i][f] == 'E' || mother->args.matrix[i][f] == 'W')
            {
                mother->gps.pos.x = f + 0.5;
                mother->gps.pos.y = i + 0.5;
                break;
            }
            f++;
        }
        i++;
    }
    find_direction(mother);
    mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x)] = '0';
}