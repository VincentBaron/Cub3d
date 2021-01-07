/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:37:04 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/07 17:37:17 by vbaron           ###   ########.fr       */
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
    int f;
    int temp;
    
    i = 0;
    while (i < mother->sprite.sprite_count)
    {
        f = i;
        while (f < mother->sprite.sprite_count)
        {
            if (mother->sprite.sprite_distance[f] > mother->sprite.sprite_distance[i])
            {    
                temp = mother->sprite.sprite_distance[i];
                mother->sprite.sprite_distance[i] = mother->sprite.sprite_distance[f];
                mother->sprite.sprite_distance[f] = mother->sprite.sprite_distance[i];
                i = -1;
                break;
            }
            f++;   
        }
        i++;
    }
}

void    sprite_display(t_general *mother)
{
    int i;

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

    int x;
    x = 0;
    while (mother->sprite.sprite_distance[x])
    {
        printf("sprite distance: %d", mother->sprite.sprite_distance[x]);
        x++;
    }
}

/*for(int i = 0; i < numSprites; i++)
    {
      spriteOrder[i] = i;
      spriteDistance[i] = ((posX - sprite[i].x) * (posX - sprite[i].x) + (posY - sprite[i].y) * (posY - sprite[i].y)); //sqrt not taken, unneeded
    }
    sortSprites(spriteOrder, spriteDistance, numSprites);

    //after sorting the sprites, do the projection and draw them
    for(int i = 0; i < numSprites; i++)
    {
      //translate sprite position to relative to camera
      double spriteX = sprite[spriteOrder[i]].x - posX;
      double spriteY = sprite[spriteOrder[i]].y - posY;

      //transform sprite with the inverse camera matrix
      // [ planeX   dirX ] -1                                       [ dirY      -dirX ]
      // [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
      // [ planeY   dirY ]                                          [ -planeY  planeX ]

      double invDet = 1.0 / (planeX * dirY - dirX * planeY); //required for correct matrix multiplication

      double transformX = invDet * (dirY * spriteX - dirX * spriteY);
      double transformY = invDet * (-planeY * spriteX + planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D

      int spriteScreenX = int((w / 2) * (1 + transformX / transformY));

      //calculate height of the sprite on screen
      int spriteHeight = abs(int(h / (transformY))); //using 'transformY' instead of the real distance prevents fisheye
      //calculate lowest and highest pixel to fill in current stripe
      int drawStartY = -spriteHeight / 2 + h / 2;
      if(drawStartY < 0) drawStartY = 0;
      int drawEndY = spriteHeight / 2 + h / 2;
      if(drawEndY >= h) drawEndY = h - 1;

      //calculate width of the sprite
      int spriteWidth = abs( int (h / (transformY)));
      int drawStartX = -spriteWidth / 2 + spriteScreenX;
      if(drawStartX < 0) drawStartX = 0;
      int drawEndX = spriteWidth / 2 + spriteScreenX;
      if(drawEndX >= w) drawEndX = w - 1;*/