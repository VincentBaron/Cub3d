/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 10:34:46 by vincentbaro       #+#    #+#             */
/*   Updated: 2020/12/02 10:42:23 by vincentbaro      ###   ########.fr       */
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
}