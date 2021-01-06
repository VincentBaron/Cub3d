/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 17:27:55 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/06 12:16:14 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void    draw_line(t_general *mother)
{
    int y;
    double text_pos;
    int text_y;
    int text_index;
    double step;

    if (mother->dda.side_pos == 1 && mother->gps.ray.y < 0)
        text_index = 0;
    if (mother->dda.side_pos == 1 && mother->gps.ray.y > 0)
        text_index = 1;
    if (mother->dda.side_pos == 0 && mother->gps.ray.x > 0)
        text_index = 2;
    if (mother->dda.side_pos == 0 && mother->gps.ray.x < 0)
        text_index = 3;
    texture_calculation(mother, text_index);
    y = mother->dda.line_start;
    step = 1.0 * mother->args.text[text_index].text_height / mother->dda.wall_height;
    text_pos = (mother->dda.line_start - mother->dda.wall_height / 2 + mother->dda.line_end / 2) * step;
    while (y < mother->dda.line_end)
    {
        text_y = (int)text_pos & (mother->args.text[text_index].text_height - 1);
        text_pos += step;
        mother->mlx.img_ray.color = *(unsigned int *)(mother->args.text[text_index].img_text.addr + mother->args.text[text_index].img_text.size_line * text_y + mother->map.text_pos * mother->args.text[text_index].img_text.bpp / 8);
        draw_pixel(&(mother->mlx.img_ray), mother->mlx.slice, y);
        y++;
    }
}

void    draw_wall(t_general *mother)
{
    mother->dda.wall_height = (int)(mother->args.R[1] / mother->dda.perpWallDist);
    mother->dda.line_start = -(mother->dda.wall_height) / 2 + mother->args.R[1] / 2;
    if (mother->dda.line_start < 0)
        mother->dda.line_start = 0;
    mother->dda.line_end = mother->dda.wall_height / 2 + mother->args.R[1] / 2;
    if (mother->dda.line_end >= mother->args.R[1])
        mother->dda.line_end = mother->args.R[1] - 1;
    draw_line(mother);
}

void    movement(t_general *mother)
{
    double old_dir_x;
    double old_plane_x;
    
    if (mother->gps.move.y == -1)
    {
        if (mother->args.matrix[(int)(mother->gps.pos.y + mother->gps.dir.y * MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
            mother->gps.pos.y += mother->gps.dir.y * MOVE_SPEED;
        if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x + mother->gps.dir.x * MOVE_SPEED)] == '0')
            mother->gps.pos.x += mother->gps.dir.x * MOVE_SPEED;
    }
    if (mother->gps.move.y == 1)
    {
        if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x - mother->gps.dir.x * MOVE_SPEED)] == '0')
            mother->gps.pos.x -= mother->gps.dir.x * MOVE_SPEED;
        if (mother->args.matrix[(int)(mother->gps.pos.y - mother->gps.dir.y * MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
            mother->gps.pos.y -= mother->gps.dir.y * MOVE_SPEED;
    }
    if (mother->gps.rot_left == 1)
    {
        old_dir_x = mother->gps.dir.x;
        mother->gps.dir.x = mother->gps.dir.x * cosf(-ROT_SPEED) - mother->gps.dir.y * sinf(-ROT_SPEED);
        mother->gps.dir.y = old_dir_x * sinf(-ROT_SPEED) + mother->gps.dir.y * cosf(-ROT_SPEED);
        old_plane_x = mother->gps.plane.x;
        mother->gps.plane.x = mother->gps.plane.x * cosf(-ROT_SPEED) - mother->gps.plane.y * sinf(-ROT_SPEED);
        mother->gps.plane.y = old_plane_x * sinf(-ROT_SPEED) + mother->gps.plane.y * cosf(-ROT_SPEED);
    }
    if (mother->gps.rot_right == 1)
    {
        old_dir_x = mother->gps.dir.x;
        mother->gps.dir.x = mother->gps.dir.x * cosf(ROT_SPEED) - mother->gps.dir.y * sinf(ROT_SPEED);
        mother->gps.dir.y = old_dir_x * sinf(ROT_SPEED) + mother->gps.dir.y * cosf(ROT_SPEED);
        old_plane_x = mother->gps.plane.x;
        mother->gps.plane.x = mother->gps.plane.x * cosf(ROT_SPEED) - mother->gps.plane.y * sinf(ROT_SPEED);
        mother->gps.plane.y = old_plane_x * sinf(ROT_SPEED) + mother->gps.plane.y * cosf(ROT_SPEED);
    }
    if (mother->gps.move.x == -1)
    {
        if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x - mother->gps.plane.x * MOVE_SPEED)] == '0')
            mother->gps.pos.x -= mother->gps.plane.x * MOVE_SPEED;
        if (mother->args.matrix[(int)(mother->gps.pos.y - mother->gps.plane.y * MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
            mother->gps.pos.y -= mother->gps.plane.y * MOVE_SPEED;
    }
    if (mother->gps.move.x == 1)
    {
        if (mother->args.matrix[(int)(mother->gps.pos.y)][(int)(mother->gps.pos.x + mother->gps.plane.x * MOVE_SPEED)] == '0')
            mother->gps.pos.x += mother->gps.plane.x * MOVE_SPEED;
        if (mother->args.matrix[(int)(mother->gps.pos.y + mother->gps.plane.y * MOVE_SPEED)][(int)(mother->gps.pos.x)] == '0')
            mother->gps.pos.y += mother->gps.plane.y * MOVE_SPEED;
    }

}

void    raycasting(t_general *mother)
{
    mother->mlx.slice = 0;
    while (mother->mlx.slice < mother->args.R[0])
    {
        mother->gps.camera.x = 2 * mother->mlx.slice / (double)(mother->args.R[0]) - 1;
        mother->gps.ray.x = mother->gps.dir.x + mother->gps.camera.x * mother->gps.plane.x;
        mother->gps.ray.y = mother->gps.dir.y + mother->gps.camera.x * mother->gps.plane.y;
        distance_calculations(mother);
        wall_position_calculation(mother);
        //define_wall_color(mother);
        draw_wall(mother);
        (mother->mlx.slice)++;
    }
}