/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/23 15:31:48 by vbaron            #+#    #+#             */
/*   Updated: 2020/11/06 09:52:36 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void   pixel_color_map(t_general *mother, char *type)
{
     if (ft_strncmp(type, "floor", ft_strlen(type)) == 0)
          mother->mlx.img_map.color = (255 << 16) + (255 << 8) + 255;
     if (ft_strncmp(type, "wall", ft_strlen(type)) == 0)
          mother->mlx.img_map.color = (0 << 16) + (0 << 8) + 0;
     if (ft_strncmp(type, "out", ft_strlen(type)) == 0)
          mother->mlx.img_map.color = (172 << 16) + (93 << 8) + 93;
     if (ft_strncmp(type, "player", ft_strlen(type)) == 0)
          mother->mlx.img_map.color = (70 << 16) + (70 << 8) + 70;
     if (ft_strncmp(type, "sprite", ft_strlen(type)) == 0)
          mother->mlx.img_map.color = (32 << 16) + (178 << 8) + 170;
}

void draw_square(t_general *mother, char *type)
{
     int x;
     int y;

     y = 0;
     while( y <= mother->map.size_y)
     {
          x = 0;
          while (x <= mother->map.size_x)
          {
                    
               (x < 1 || x > (mother->map.size_x - 1)) || (y < 1 || y > (mother->map.size_y - 1)) ? pixel_color_map(mother, "out") : pixel_color_map(mother, type);
               draw_pixel(&(mother->mlx.img_map), y + mother->map.size_y * mother->map.track_y, x + mother->map.size_x * mother->map.track_x);
               x++;
          }
          y++;
     }
}

void draw_map_ray(t_general *mother)
{
     int length;

     length = sinf(mother->raycast.angle) * (mother->raycast.dist_inter) * mother->map.size_x;
     while (length > 0)
     {
          draw_pixel(&(mother->mlx.img_map), (int)(mother->gps.pos.x * mother->map.size_x + length * cosf(mother->raycast.angle)), (int)(mother->gps.pos.y * mother->map.size_y + length * sinf(mother->raycast.angle)));
          length--;
     }
}

void draw_player(t_general *mother)
{
     int x;
     int y;
     

     pixel_color_map(mother, "player");
     y = mother->map.size_y / 4;
     while( y < (3 * mother->map.size_y / 4))
     {
          x = mother->map.size_x / 4;;
          while (x < (3 * mother->map.size_x / 4))
          {
                    draw_pixel(&(mother->mlx.img_map), x + 1 + mother->map.size_x * (mother->gps.pos.x - 0.5), y + 1 + mother->map.size_y * (mother->gps.pos.y - 0.5));
                    x++;
          }
          y++;
     }
}

void draw_map(t_general *mother)
{
     mother->map.track_x = 0;
     while(mother->args.matrix[mother->map.track_x])
     {
          mother->map.track_y = 0;
          while (mother->args.matrix[mother->map.track_x][mother->map.track_y])
          {
               if (mother->args.matrix[mother->map.track_x][mother->map.track_y] == ' ')
                    draw_square(mother, "out");
               if (mother->args.matrix[mother->map.track_x][mother->map.track_y] == '1')
                    draw_square(mother, "wall");
               if (mother->args.matrix[mother->map.track_x][mother->map.track_y] == '0')
                    draw_square(mother, "floor");
               if (mother->args.matrix[mother->map.track_x][mother->map.track_y] == 'N' || mother->args.matrix[mother->map.track_x][mother->map.track_y] == 'S' || mother->args.matrix[mother->map.track_x][mother->map.track_y] == 'E' ||mother->args.matrix[mother->map.track_x][mother->map.track_y] == 'W')
               {
                    draw_square(mother, "floor");
                    mother->args.matrix[mother->map.track_x][mother->map.track_y] = '0';
               }
               if (mother->args.matrix[mother->map.track_x][mother->map.track_y] == '2')
                    draw_square(mother, "sprite");    
               mother->map.track_y++;
          }
          mother->map.track_x++;
     }
}

int       check_angle(float angle, float a_max, float a_min)
{
     if (angle <= a_max && angle >= a_min)
          return (-1);
     else
          return (1);
}

void    redefine_position(t_general *mother)
{
    float angle;

     angle = mother->gps.angle;
     if (mother->gps.rot_left == 1)
          mother->gps.angle += PI / 8;
     if (mother->gps.rot_right == 1)
          mother->gps.angle -= PI / 8;
     if (mother->gps.move.y == -1 && mother->args.matrix[(int)(mother->gps.pos.y - 0.35)][(int)(mother->gps.pos.x - 0.26)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y - 0.35)][(int)(mother->gps.pos.x + 0.26)] == '0')
     {
          mother->gps.pos.y += check_angle(angle, PI, 0) * 0.1 * sinf(angle);
          mother->gps.pos.x += check_angle(angle, (3 * PI) / 2, PI / 2) * 0.1 * cosf(angle);
     }
     else if (mother->gps.move.y == 1 && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x - 0.26)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x + 0.26)] == '0')
     {
          mother->gps.pos.y += check_angle(angle, 2 * PI, PI) * 0.1 * sinf(angle);
          mother->gps.pos.x += check_angle(angle, PI / 2, 3 * PI / 2) * 0.1 * cosf(angle);
     }
     else if (mother->gps.move.x == -1 && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x - 0.26)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x + 0.26)] == '0')
     {
          mother->gps.pos.y += check_angle(angle + PI / 2, 2 * PI, PI) * 0.1 * sinf(angle + PI / 2);
          mother->gps.pos.x += check_angle(angle + PI / 2, PI / 2, 3 * PI / 2) * 0.1 * cosf(angle + PI / 2);
     }
     else if (mother->gps.move.x == 1 && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x - 0.26)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x + 0.26)] == '0')
     {
          mother->gps.pos.y += check_angle(angle - PI / 2, 2 * PI, PI) * 0.1 * sinf(angle - PI / 2);
          mother->gps.pos.x += check_angle(angle - PI / 2, PI / 2, 3 * PI / 2) * 0.1 * cosf(angle - PI / 2);
     } 
     /*if (mother->gps.move.y == -1 && mother->args.matrix[(int)(mother->gps.pos.y - 0.35)][(int)(mother->gps.pos.x - 0.26)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y - 0.35)][(int)(mother->gps.pos.x + 0.26)] == '0')
        mother->gps.pos.y -= 0.1;        
     else if (mother->gps.move.y == 1 && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x - 0.26)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y + 0.35)][(int)(mother->gps.pos.x + 0.26)] == '0')
        mother->gps.pos.y += 0.1;
     else if (mother->gps.move.x == -1 && mother->args.matrix[(int)(mother->gps.pos.y - 0.26)][(int)(mother->gps.pos.x - 0.35)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y + 0.26)][(int)(mother->gps.pos.x - 0.35)] == '0')
        mother->gps.pos.x -= 0.1;
     else if (mother->gps.move.x == +1 && mother->args.matrix[(int)(mother->gps.pos.y - 0.26)][(int)(mother->gps.pos.x + 0.35)] == '0' && mother->args.matrix[(int)(mother->gps.pos.y + 0.26)][(int)(mother->gps.pos.x + 0.35)] == '0')
        mother->gps.pos.x +=0.1;*/
}