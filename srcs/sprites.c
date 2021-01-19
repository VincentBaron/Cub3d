/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:37:04 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/19 15:08:32 by vincentbaro      ###   ########.fr       */
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
        error(mother, 3);
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
                z++;
            }
            f++;
        }
        i++;
    }
    mother->sprite.elem[z].x = -1;
    if(!(mother->sprite.zbuffer = (int *)malloc(sizeof(int) * mother->args.R[0])))
        error(mother, 3);
    if(!(mother->sprite.sprite_order = (int *)malloc(sizeof(int) * mother->sprite.sprite_count)))
        error(mother, 3);
    if(!(mother->sprite.sprite_distance = (int *)malloc(sizeof(int) * mother->sprite.sprite_count)))
        error(mother, 3);
}

void    sort_sprites(t_general *mother)
{
    int i;
    int dist_inf;
    int dist_sup;
    t_coor temp;

    i = 0;
    while (i + 1 < mother->sprite.sprite_count)
    {
        dist_inf = ((mother->gps.pos.x - mother->sprite.elem[i].x) * (mother->gps.pos.x - mother->sprite.elem[i].x) + (mother->gps.pos.y - mother->sprite.elem[i].y) * (mother->gps.pos.y - mother->sprite.elem[i].y));
        dist_sup = ((mother->gps.pos.x - mother->sprite.elem[i + 1].x) * (mother->gps.pos.x - mother->sprite.elem[i + 1].x) + (mother->gps.pos.y - mother->sprite.elem[i + 1].y) * (mother->gps.pos.y - mother->sprite.elem[i + 1].y));
        if (dist_inf < dist_sup)
        {
            temp = mother->sprite.elem[i];
            mother->sprite.elem[i] = mother->sprite.elem[i + 1];
            mother->sprite.elem[i + 1] = temp;
            i = 0;
        }
        else
            i++;
    }
}

void    sprite_distance(t_general *mother, int i)
{
    mother->sprite.pos.x = mother->sprite.elem[i].x - mother->gps.pos.x + 0.5; // RAJOUTER + 0.5
    mother->sprite.pos.y = mother->sprite.elem[i].y - mother->gps.pos.y + 0.5; // RAJOUTER + 0.5
    mother->sprite.inv_det = 1.0 / (mother->gps.plane.x * mother->gps.dir.y - mother->gps.dir.x * mother->gps.plane.y); // PLANE Y A LA FIN
    mother->sprite.transform.x = mother->sprite.inv_det * (mother->gps.dir.y * mother->sprite.pos.x - mother->gps.dir.x * mother->sprite.pos.y);
    mother->sprite.transform.y = mother->sprite.inv_det * (-mother->gps.plane.y * mother->sprite.pos.x + mother->gps.plane.x * mother->sprite.pos.y);
    mother->sprite.spriteScreen = (int)((mother->args.R[0] / 2) * (1 + mother->sprite.transform.x / mother->sprite.transform.y));
    mother->sprite.sprite_height = abs((int)(mother->args.R[1] / (mother->sprite.transform.y))); // UNE PARENTHESE RAJOUTÉ
    mother->sprite.sprite_width = abs((int)(mother->args.R[1] / (mother->sprite.transform.y)));

}

void    drawing_constrains(t_general *mother)
{
    mother->sprite.draw_start.y = -mother->sprite.sprite_height / 2 + mother->args.R[1] / 2;
    if (mother->sprite.draw_start.y < 0)
        mother->sprite.draw_start.y = 0;
    mother->sprite.draw_end.y = mother->sprite.sprite_height / 2 + mother->args.R[1] / 2;
    if (mother->sprite.draw_end.y >= mother->args.R[1])
        mother->sprite.draw_end.y = mother->args.R[1] - 1;
    mother->sprite.draw_start.x = -mother->sprite.sprite_width / 2 + mother->sprite.spriteScreen;
    if (mother->sprite.draw_start.x < 0)
        mother->sprite.draw_start.x = 0;
    mother->sprite.draw_end.x = mother->sprite.sprite_width / 2 + mother->sprite.spriteScreen;
    if (mother->sprite.draw_end.x >= mother->args.R[0])
        mother->sprite.draw_end.x = mother->args.R[0] - 1;
}

static void    sprite_display(t_general *mother, int j, int stripe)
{
    int d;
    int txtr_y;

    d = j * 256 - mother->args.R[1] * 128 + mother->sprite.sprite_height * 128;
    txtr_y = ((d * mother->args.text[4].text_height) / mother->sprite.sprite_height) / 256;
    mother->mlx.img_ray.color = *(unsigned int *)(mother->args.text[4].img_text.addr + mother->args.text[4].img_text.size_line * txtr_y + mother->sprite.tex.x * (mother->args.text[4].img_text.bpp / 8)); //RAJOUT DE PARENTHESE
    if ((mother->mlx.img_ray.color & 0x00FFFFFF) != 0)
        draw_pixel(&(mother->mlx.img_ray), stripe, j);
}

void    sprite_projection(t_general *mother)
{
    int i;
    int j;
    int stripe;
    
    i = 0;
    while (i < mother->sprite.sprite_count)
    {
        sprite_distance(mother, i);
        drawing_constrains(mother);
        stripe = mother->sprite.draw_start.x;
        while (stripe < mother->sprite.draw_end.x)
        {
            mother->sprite.tex.x = (int)(256 * (stripe - (-mother->sprite.sprite_width / 2 + mother->sprite.spriteScreen)) * mother->args.text[4].text_width / mother->sprite.sprite_width) / 256; // SPRITE WIDTH (SECOND) MAUVAIS
            if (mother->sprite.transform.y > 0 && stripe > 0 && stripe < mother->args.R[0] && mother->sprite.transform.y < mother->sprite.zbuffer[stripe])
            {
                j = mother->sprite.draw_start.y;
                while (j < mother->sprite.draw_end.y)
                {
                    sprite_display(mother, j, stripe);
                    ++j;
                }
            }
            stripe++;
        }
        i++;
    }
}
