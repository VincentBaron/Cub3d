/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:24:18 by vincentbaro       #+#    #+#             */
/*   Updated: 2021/01/18 22:32:30 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void save_image(t_general *mother)
{
   mother->bmp.fd = open("image.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
   create_header(mother);
   fill_file(mother);
}

void    fill_file(t_general *mother)
{
    unsigned char data[4];
    t_coor pixel;

    pixel.y = 0;
    while (pixel.y < mother->args.R[1])
    {
        pixel.x = 0;
        while (pixel.x < mother->args.R[0])
        {
            *data = mother->mlx.img_ray.addr[pixel.x * mother->mlx.img_ray.bpp + pixel.y * mother->mlx.img_ray.size_line / 8];
            if (write(mother->bmp.fd, data, 4) < 0)
                error(mother, 5);
            pixel.x++;
        }
        pixel.y++;
    }
}

void    create_header(t_general  *mother)
{
    int i;
    
    i = 0;
    mother->bmp.file_size = 54 + 3 * mother->args.R[0] * mother->args.R[1];
    ft_memset(mother->bmp.header, 0, 54);
    mother->bmp.header[0] = 'B';
    mother->bmp.header[1] = 'M';
    mother->bmp.header[2] = (unsigned char)mother->bmp.file_size;
    mother->bmp.header[3] = (unsigned char)mother->bmp.file_size >> 8;
    mother->bmp.header[4] = (unsigned char)mother->bmp.file_size >> 16;
    mother->bmp.header[5] = (unsigned char)mother->bmp.file_size >> 24;
    mother->bmp.header[10] = (unsigned char)54;
    mother->bmp.header[14] = (unsigned char)40;
    mother->bmp.header[18] = (unsigned char)mother->args.R[0];
    mother->bmp.header[19] = (unsigned char)mother->args.R[0] >> 8;
    mother->bmp.header[20] = (unsigned char)mother->args.R[0] >> 16;
    mother->bmp.header[21] = (unsigned char)mother->args.R[0] >> 24;
    mother->bmp.header[22] = (unsigned char)mother->args.R[1];
    mother->bmp.header[23] = (unsigned char)mother->args.R[1] >> 8;
    mother->bmp.header[24] = (unsigned char)mother->args.R[1] >> 16;
    mother->bmp.header[25] = (unsigned char)mother->args.R[1] >> 24;
    mother->bmp.header[26] = (unsigned char)1;
    mother->bmp.header[28] = (unsigned char)32;
    if (write(mother->bmp.fd, mother->bmp.header, 54) < 0)
        error(mother, 5);
}