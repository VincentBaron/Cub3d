/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 15:07:46 by vbaron            #+#    #+#             */
/*   Updated: 2020/11/06 10:22:57 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char check_collision(t_general *mother, t_float inter)
{
    if(mother->args.matrix[(int)inter.y][(int)inter.x] == 0)
        return(-1);
    return (mother->args.matrix[(int)inter.y][(int)inter.x]);
}

float    horizontal_intersection_calculation(t_general *mother)
{
    t_float inter;
    t_float offset;

    offset.x = 1.0 / tanf(mother->raycast.angle);
    offset.y = 1.0;

    inter.y = (int)(mother->gps.pos.y) + (mother->raycast.angle < PI && mother->raycast.angle > 0 ? -0.01 : +1);
    inter.x = mother->gps.pos.x + (mother->gps.pos.y - inter.y) / tanf(mother->raycast.angle);
    while(check_collision(mother, inter) == -1)
    {
        inter.y += (mother->raycast.angle < PI && mother->raycast.angle > 0 ? -offset.y : +offset.y);
        inter.x += offset.x;
    }
    return(inter.y / sinf(mother->raycast.angle));
}

float    vertical_intersection_calculation(t_general *mother)
{
    t_float inter;
    t_float offset;

    offset.x = 1.0;
    offset.y = 1.0 / tanf(mother->raycast.angle);

    inter.x = (int)(mother->gps.pos.x) + (mother->raycast.angle < PI / 2 && mother->raycast.angle > (3 * PI / 2) ? +1 : -0.01);
    inter.y = mother->gps.pos.y + (mother->gps.pos.x - inter.x) / tanf(mother->raycast.angle);
    while(check_collision(mother, inter) == -1)
    {
        inter.x += (mother->raycast.angle < PI / 2 && mother->raycast.angle > (3 * PI / 2) ? +offset.x : -offset.x);
        inter.y += offset.y;
    }
    return(inter.y / sinf(mother->raycast.angle));
}

void    check_intersection(t_general *mother)
{
    float Horizontal_inter = horizontal_intersection_calculation(mother);
    float vertical_inter = vertical_intersection_calculation(mother);

    (void)Horizontal_inter;
    (void)vertical_inter;

    ft_putchar_fd('\n', 1);
    if (vertical_intersection_calculation(mother) == horizontal_intersection_calculation(mother))
        //draw_intersection
    if (vertical_intersection_calculation(mother) >= horizontal_intersection_calculation(mother))
        mother->raycast.dist_inter = horizontal_intersection_calculation(mother);
    if (vertical_intersection_calculation(mother) < horizontal_intersection_calculation(mother))
        mother->raycast.dist_inter = vertical_intersection_calculation(mother);
    mother->raycast.pos_inter.x = mother->raycast.dist_inter * cosf(mother->raycast.angle);
    mother->raycast.pos_inter.y = mother->raycast.dist_inter * sinf(mother->raycast.angle);
}