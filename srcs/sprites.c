/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:37:04 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/08 12:25:03 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/cub3d.h"

void    create_sprites(t_general *mother)
{
    int i;
    int f;
    int z;

    i = 0;
    mother->sprite.sprite_count = 0;
    while (mother->args.matrix[i])
    {
        f = 0;
        while (mother->args.matrix[i][f])
        {
            if (mother->args.matrix[i][f] == '2')
                mother->sprite.sprite_count++;
            f++;
        }
        i++;
    }
    if (!(mother->sprite.elem = (t_coor *)malloc(sizeof(t_coor) * (mother->sprite.sprite_count + 1))))
    {
        error();
        return ;
    }
    i = 0;
    z = 0;
    while (mother->args.matrix[i])
    {
        f = 0;
        while (mother->args.matrix[i][f])
        {
            if (mother->args.matrix[i][f] == '2')
            {
                mother->sprite.elem[z].x = f;
                mother->sprite.elem[z].y = i;
                //mother->args.matrix[i][f] = '0';
                z++;
            }
            f++;
        }
        i++;
    }
    mother->sprite.elem[z].x = -1;
    if(!(mother->sprite.zbuffer = (int *)malloc(sizeof(int) * mother->args.R[0])))
    {
        error();
        return ;
    }
}

void    sort_sprites(t_general *mother)
{
    int i;
	int temp;

	i = 0;
	while (i + 1 < mother->sprite.sprite_count)
	{
		if (mother->sprite.sprite_distance[i + 1] > mother->sprite.sprite_distance[i])
		{
			temp = mother->sprite.sprite_distance[i];
			mother->sprite.sprite_distance[i] = mother->sprite.sprite_distance[i + 1];
			mother->sprite.sprite_distance[i + 1] = temp;
            temp = mother->sprite.sprite_order[i];
			mother->sprite.sprite_order[i] = mother->sprite.sprite_order[i + 1];
			mother->sprite.sprite_order[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

void    sprite_display(t_general *mother)
{
    int i;
    
    create_sprites(mother);
    if(!(mother->sprite.sprite_order = (int *)malloc(sizeof(int) * mother->sprite.sprite_count)))
    {
        error();
        return ;
    }
     if(!(mother->sprite.sprite_distance = (int *)malloc(sizeof(int) * mother->sprite.sprite_count)))
    {
        error();
        return ;
    }
    i = 0;
    while (i < mother->sprite.sprite_count)
    {
        mother->sprite.sprite_order[i] = i;
        mother->sprite.sprite_distance[i] = ((mother->gps.pos.x - mother->sprite.elem[i].x) * (mother->gps.pos.x - mother->sprite.elem[i].x) + (mother->gps.pos.y - mother->sprite.elem[i].y) * (mother->gps.pos.y - mother->sprite.elem[i].y)); 
        i++;
    }    
    sort_sprites(mother);
    //exit(0);
    sprite_projection(mother);
}

void    sprite_projection(t_general *mother)
{
    int i;
    t_coor sprite;
    double invDet;
    t_coor transform;
    int slice;
    int y;
    int d;

     i = 0;
    while (i < mother->sprite.sprite_count)
    {
        printf("elem[%d].x: %d\n", i, mother->sprite.elem[i].x);
        printf("elem[%d].y: %d\n", i, mother->sprite.elem[i].y);
        printf("sprite_distance[%d]: %d\n", i, mother->sprite.sprite_distance[i]);
        printf("sprite_order[%d]: %d\n", i, mother->sprite.sprite_order[i]);
        i++;
    }
    i = 0;
    while (i < mother->sprite.sprite_count)
    {
        sprite.x = mother->sprite.elem[mother->sprite.sprite_order[i]].x - mother->gps.pos.x;
        sprite.y = mother->sprite.elem[mother->sprite.sprite_order[i]].y - mother->gps.pos.y;
        invDet = 1.0 / (mother->gps.plane.x * mother->gps.dir.y - mother->gps.dir.x * mother->gps.plane.y);
        transform.x = invDet * (mother->gps.dir.y * sprite.x - mother->gps.dir.x * sprite.y);
        transform.y = invDet * (-(mother->gps.plane.y) * sprite.x + mother->gps.plane.x * sprite.y);
        mother->sprite.spriteScreen = (int)((mother->args.R[0] / 2) * (1 + transform.x / transform.y));
        mother->sprite.sprite_height = abs((int)(mother->args.R[1] / transform.y));
        mother->sprite.draw_start.y = -(mother->sprite.sprite_height) / 2 + mother->args.R[1] / 2;
        if (mother->sprite.draw_start.y < 0)
            mother->sprite.draw_start.y = 0;
        mother->sprite.draw_end.y = mother->sprite.sprite_height / 2 + mother->args.R[1] / 2;
        if(mother->sprite.draw_end.y >= mother->args.R[1])
            mother->sprite.draw_end.y = mother->args.R[1] - 1;
        mother->sprite.sprite_width = abs((int)(mother->args.R[1] /transform.y));
        mother->sprite.draw_start.x = -(mother->sprite.sprite_width) / 2 + mother->sprite.spriteScreen;
        if (mother->sprite.draw_start.x < 0)
            mother->sprite.draw_start.x = 0;
        mother->sprite.draw_start.x = mother->sprite.sprite_width / 2 + mother->sprite.spriteScreen;
        if (mother->sprite.draw_end.x >= mother->args.R[0])
            mother->sprite.draw_end.x = mother->args.R[0] - 1;
        slice = mother->sprite.draw_start.x;
        while (slice < mother->sprite.draw_end.x)
        {
            mother->sprite.tex.x = (int)(256 * (slice - (-mother->sprite.sprite_width / 2 + mother->sprite.spriteScreen)) * mother->args.text[4].text_width / mother->sprite.sprite_width) / 256;
            if (transform.y > 0 && slice > 0 && slice < mother->args.R[0] && transform.y < mother->sprite.zbuffer[slice])
            {
                y = mother->sprite.draw_start.y;
                while (y < mother->sprite.draw_end.y)
                {
                    d = y * 256 - mother->args.R[1] * 128 + mother->sprite.sprite_height * 128;
                    mother->sprite.tex.y = ((d * mother->args.text[4].text_height) / mother->sprite.sprite_height) / 256;
                    //mother->mlx.img_ray.color = *(unsigned int *)(mother->args.text[4].img_text.addr + mother->args.text[4].img_text.size_line * mother->sprite.tex.y + mother->sprite.tex.x * mother->args.text[4].img_text.bpp / 8);
                    //if ((mother->mlx.img_ray.color & 0x00FFFFFF) != 0) 
                    //    draw_pixel(&(mother->mlx.img_ray), slice, y);
                    y++;
                }
            }
            slice++;
        }
        i++;
    }
}
