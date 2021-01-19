/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:24:18 by vincentbaro       #+#    #+#             */
/*   Updated: 2021/01/19 16:06:00 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void save_image(t_general *mother)
{
    create_images(mother);
    set_background(mother);
    raycasting(mother);   
    mother->bmp.fd = open("bitmap.bmp", O_CREAT | O_TRUNC, S_IRWXU);
    create_header(mother);
    fill_file(mother);
    //close(mother->bmp.fd);
    //free(mother->mlx.img_ray.image);
    //free(mother->mlx.img_ray.addr);
}

void    fill_file(t_general *mother)
{
    int i;
    int j;
    unsigned char buf[4];

    i = mother->args.R[0] * (mother->args.R[1] - 1);
    while (i >= 0)
    {
        j = 0;
        while (j < mother->args.R[0])
        {
            buf[0] = (unsigned char)(mother->mlx.img_ray.addr[i] % 256);
            buf[1] = (unsigned char)(mother->mlx.img_ray.addr[i] / 256 % 256);
            buf[2] = (unsigned char)(mother->mlx.img_ray.addr[i] / 256 / 256 % 256);
            buf[3] = (unsigned char)0;
            write(mother->bmp.fd, buf, 4);
            i++;
            j++;
        }
        i -= 2 * mother->args.R[0];
    }
}

void    create_header(t_general  *mother)
{
    int i;
    unsigned char header[54];
    int file_size;
    
    i = 0;
    file_size = 54 + 3 * mother->args.R[0] * mother->args.R[1];
    while (i++ < 53)
        header[i] = 0;
    header[0] = 'B';
    header[1] = 'M';
    header[2] = (unsigned char)file_size;
    header[3] = (unsigned char)file_size >> 8;
    header[4] = (unsigned char)file_size >> 16;
    header[5] = (unsigned char)file_size >> 24;
    header[10] = (unsigned char)54;
    header[14] = (unsigned char)40;
    header[18] = (unsigned char)mother->args.R[0];
    header[19] = (unsigned char)mother->args.R[0] >> 8;
    header[20] = (unsigned char)mother->args.R[0] >> 16;
    header[21] = (unsigned char)mother->args.R[0] >> 24;
    header[22] = (unsigned char)mother->args.R[1];
    header[23] = (unsigned char)mother->args.R[1] >> 8;
    header[24] = (unsigned char)mother->args.R[1] >> 16;
    header[25] = (unsigned char)mother->args.R[1] >> 24;
    header[26] = (unsigned char)1;
    header[28] = (unsigned char)32;
    //if (write(mother->bmp.fd, header, 54) < 0)
    //    error(mother, 5);
    write(mother->bmp.fd, header, 54);
}