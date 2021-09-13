/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 16:49:29 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/13 19:01:47 by user42           ###   ########.fr       */
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

void ft_clean(t_general *mother)
{
     int	i;

	i = 0;
	while (mother->args.matrix[i])
	{
		if (mother->args.matrix[i])
			ft_free(mother->args.matrix[i]);
		i++;
	}
     if (mother->args.matrix)
          free(mother->args.matrix);
     i = 0;
     while (i < 5)
     {
          if (mother->args.text[i].img_text.image)
               mlx_destroy_image(mother->mlx.ptr, mother->args.text[i].img_text.image);
          if (mother->args.text[i].path)
               free(mother->args.text[i].path);
          i++;
     }
     if (mother->sprite.elem)
          free(mother->sprite.elem);
     if (mother->sprite.zbuffer)
          free(mother->sprite.zbuffer);
     if (mother->sprite.zbuffer)
          free(mother->sprite.sprite_distance);
     if (mother->sprite.sprite_order)
          free(mother->sprite.sprite_order);
     if (mother->mlx.img_sprite.image)
          mlx_destroy_image(mother->mlx.ptr, mother->mlx.img_sprite.image);
     if (mother->mlx.img_ray.image)
          mlx_destroy_image(mother->mlx.ptr, mother->mlx.img_ray.image);
     if (mother->mlx.img_map.image)
          mlx_destroy_image(mother->mlx.ptr, mother->mlx.img_map.image);
     if (mother->mlx.win)
          mlx_destroy_window(mother->mlx.ptr, mother->mlx.win);
     if (mother->mlx.ptr)
     {
          mlx_destroy_display(mother->mlx.ptr);
          free(mother->mlx.ptr);
     }
     exit(1);
}

int key_press(int keycode, t_general *mother)
{
     mother->gps.event = 1;
     //movement_to_zero(mother);
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
     else if (keycode == ESC)
          ft_clean(mother);
     printf("keycode: %d\n", keycode);
     return (0);
}

int key_release(int keycode, t_general *mother)
{
     //mother->gps.event = 0;
     if (keycode == UP)
          mother->gps.move.y = 0;
     else if (keycode == DOWN)
          mother->gps.move.y = 0;
     else if (keycode == LEFT)
          mother->gps.move.x = 0;
     else if (keycode == RIGHT)
          mother->gps.move.x = 0;
     else if (keycode == ROT_LEFT)
          mother->gps.rot_left = 0;
     else if (keycode == ROT_RIGHT)
          mother->gps.rot_right = 0;
     return (0);
}

void movement_to_zero(t_general *mother)
{
     mother->gps.move.y = 0;
     mother->gps.move.y = 0;
     mother->gps.move.x = 0;
     mother->gps.rot_left = 0;
     mother->gps.rot_right = 0;
}

void create_images(t_general *mother)
{
     if (mother->args.R[0] > 500 && mother->args.R[1] > 500)
     {
          mother->mlx.img_map.image = mlx_new_image(mother->mlx.ptr, mother->map.res_x, mother->map.res_y);
          mother->mlx.img_map.addr = mlx_get_data_addr(mother->mlx.img_map.image, &(mother->mlx.img_map.bpp), &(mother->mlx.img_map.size_line), &(mother->mlx.img_map.endian));
     }
     mother->mlx.img_ray.image = mlx_new_image(mother->mlx.ptr, mother->args.R[0], mother->args.R[1]);
     mother->mlx.img_ray.addr = mlx_get_data_addr(mother->mlx.img_ray.image, &(mother->mlx.img_ray.bpp), &(mother->mlx.img_ray.size_line), &(mother->mlx.img_ray.endian));
}

void display_images(t_general *mother)
{
     mlx_put_image_to_window(mother->mlx.ptr, mother->mlx.win, mother->mlx.img_ray.image, 0, 0);    
     if (mother->args.R[0] > 500 && mother->args.R[1] > 500)
          mlx_put_image_to_window(mother->mlx.ptr, mother->mlx.win, mother->mlx.img_map.image, 0, 0);
}

int events_list(t_general *mother)
{
     if (mother->mlx.esc == 0)
     {
          set_background(mother);
          movement(mother);
          if (mother->args.R[0] > 500 && mother->args.R[1] > 500)
               draw_map(mother);
          raycasting(mother);
          display_images(mother);
     }
     return (0);
}
    

void    game_start(t_general *mother)
{    
     create_images(mother);
     mlx_hook(mother->mlx.win, KEY_PRESS, 1L<<0, &key_press, mother);
     mlx_hook(mother->mlx.win, KEY_RELEASE, 1L<<1, &key_release, mother);
     mlx_loop_hook(mother->mlx.ptr, &events_list, mother);
     mlx_loop(mother->mlx.ptr);
}