/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 19:24:18 by vincentbaro       #+#    #+#             */
/*   Updated: 2021/01/19 15:08:15 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void save_image(t_general *mother)
{
    create_images(mother);
    set_background(mother);
    raycasting(mother);   
    mother->bmp.fd = open("bitmap.bmp", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0755);
    create_file(mother); 
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

void    create_file(t_general *mother)
{
    int n;
    unsigned char header[14];
    int file_size;

    file_size = mother->args.R[0] * mother->args.R[1] * 4 + 54;
    n = 0;
    while (n < 14)
        header[n++] = (unsigned char)0;
    header[0] = (unsigned char)66;
    header[1] = (unsigned char)77;
    header[2] = (unsigned char)(file_size % 256);
	header[3] = (unsigned char)(file_size / 256 % 256);
	header[4] = (unsigned char)(file_size / 256 / 256 % 256);
	header[5] = (unsigned char)(file_size / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(mother->bmp.fd, header, 14);
}

void    create_header(t_general  *mother)
{
    int i;
    unsigned char header[40];

    i = 0;
    while (i < 40)
        header[i++] = (unsigned char)0;
    header[0] = (unsigned char)40;
    header[4] = (unsigned char)(mother->args.R[0] % 256);
	header[5] = (unsigned char)(mother->args.R[0] / 256 % 256);
	header[6] = (unsigned char)(mother->args.R[0] / 256 / 256 % 256);
	header[7] = (unsigned char)(mother->args.R[0] / 256 / 256 / 256);
	header[8] = (unsigned char)(mother->args.R[1] % 256);
	header[9] = (unsigned char)(mother->args.R[1] / 256 % 256);
	header[10] = (unsigned char)(mother->args.R[1] / 256 / 256 % 256);
	header[11] = (unsigned char)(mother->args.R[1] / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(mother->bmp.fd, header, 40);

}