/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:49:29 by vbaron            #+#    #+#             */
/*   Updated: 2020/11/05 17:14:55 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char *draw_pixel(t_img *img, int x, int y)
{
     char *dest;

     dest = (img->addr +  x * (img->bpp / 8) + y * img->size_line);
     *(unsigned int *)dest = img->color;
     return (dest);
}

int key_press(int keycode, t_general *mother)
{
     mother->gps.event = 1;
     if (keycode == UP)
          mother->gps.move.y = -1;
     else if (keycode == DOWN)
          mother->gps.move.y = 1;
     else if (keycode == LEFT)
          mother->gps.move.x = -1;
     else if (keycode == RIGHT)
          mother->gps.move.x = 1;
     else if (keycode == ROT_LEFT)
          mother->gps.rot_left = 1;
     else if (keycode == ROT_RIGHT)
          mother->gps.rot_right = 1;
     mother->gps.event = 1;
     printf("keycode: %d\n", keycode);
     return (0);
}

int key_release(int keycode, t_general *mother)
{
     mother->gps.event = 0;
     mother->gps.move.x = 0;
     mother->gps.move.y = 0;
     mother->gps.rot_left = 0;
     mother->gps.rot_right = 0;
     (void)keycode;
     return (0);
}

void create_images(t_general *mother)
{
     mother->map.size_x = 20;
     mother->map.size_y = 20;
     mother->mlx.img_map.image = mlx_new_image(mother->mlx.ptr, mother->args.R[0], mother->args.R[1]);
     mother->mlx.img_map.addr = mlx_get_data_addr(mother->mlx.img_map.image, &(mother->mlx.img_map.bpp), &(mother->mlx.img_map.size_line), &(mother->mlx.img_map.endian));
     mother->mlx.img_ray.image = mlx_new_image(mother->mlx.ptr, mother->args.R[0], mother->args.R[1]);
     mother->mlx.img_ray.addr = mlx_get_data_addr(mother->mlx.img_ray.image, &(mother->mlx.img_ray.bpp), &(mother->mlx.img_ray.size_line), &(mother->mlx.img_ray.endian));
}

void display_images(t_general *mother)
{
     mlx_put_image_to_window(mother->mlx.ptr, mother->mlx.win, mother->mlx.img_map.image, 0, 0);    
}

void movement_to_zero(t_general *mother)
{
     mother->gps.event = 0;
     mother->gps.move.x = 0;
     mother->gps.move.y = 0;
     mother->gps.rot_left = 0;
     mother->gps.rot_right = 0;
}

int events_list(t_general *mother)
{
     create_images(mother);
     redefine_position(mother);
     draw_map(mother);
     draw_player(mother);
     draw_rays(mother);
     display_images(mother);
     movement_to_zero(mother);
     return (0);
}
    

void    game_start(t_general *mother)
{    
     mother->gps.move.x = 0;
     mother->gps.move.y = 0;
     
     if (!(mother->mlx.ptr = mlx_init()))
          ft_putstr_fd("Error initialising mlx", 2);
     if (!(mother->mlx.win = mlx_new_window(mother->mlx.ptr, mother->args.R[0], mother->args.R[1], "J' aime les Moules Brite")))
          ft_putstr_fd("Error creating window", 2);
     mlx_hook(mother->mlx.win, KEY_PRESS, 1L<<0, &key_press, mother);
     mlx_hook(mother->mlx.win, KEY_RELEASE, 1L<<1, &key_release, mother);
     mlx_loop_hook(mother->mlx.ptr, &events_list, mother);
     mlx_loop(mother->mlx.ptr);
}