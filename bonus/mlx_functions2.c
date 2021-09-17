/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_functions2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 22:22:15 by user42            #+#    #+#             */
/*   Updated: 2021/09/15 11:14:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*draw_pixel(t_img *img, int x, int y)
{
	char	*dest;

	dest = (img->addr + x
			* (img->bpp / 8) + y * img->size_line);
	*(unsigned int *)dest = img->color;
	return (dest);
}

void	free_mlx(t_general *mother)
{
	if (mother->sprite.elem)
		free(mother->sprite.elem);
	if (mother->sprite.zbuffer)
		free(mother->sprite.zbuffer);
	if (mother->sprite.sprite_distance)
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
}

int	ft_clean(t_general *mother)
{
	int	i;

	i = 0;
	if (mother->args.matrix)
	{
		while (mother->args.matrix[i])
		{
			if (mother->args.matrix[i])
				ft_free(mother->args.matrix[i]);
			i++;
		}
		free(mother->args.matrix);
	}
	i = 0;
	while (i < 5)
	{
		if (mother->args.text[i].img_text.image)
			mlx_destroy_image(mother->mlx.ptr,
				mother->args.text[i].img_text.image);
		if (mother->args.text[i].path)
			free(mother->args.text[i].path);
		i++;
	}
	free_mlx(mother);
	exit(1);
}

void	create_images(t_general *mother)
{
	if (mother->args.R[0] > 500 && mother->args.R[1] > 500)
	{
		mother->mlx.img_map.image = mlx_new_image(mother->mlx.ptr,
				mother->map.res_x, mother->map.res_y);
		mother->mlx.img_map.addr = mlx_get_data_addr(mother->mlx.img_map.image,
				&(mother->mlx.img_map.bpp), &(mother->mlx.img_map.size_line),
				&(mother->mlx.img_map.endian));
	}
	mother->mlx.img_ray.image = mlx_new_image(mother->mlx.ptr,
			mother->args.R[0], mother->args.R[1]);
	mother->mlx.img_ray.addr = mlx_get_data_addr(mother->mlx.img_ray.image,
			&(mother->mlx.img_ray.bpp), &(mother->mlx.img_ray.size_line),
			&(mother->mlx.img_ray.endian));
}

void	display_images(t_general *mother)
{
	mlx_put_image_to_window(mother->mlx.ptr,
		mother->mlx.win, mother->mlx.img_ray.image, 0, 0);
	if (mother->args.R[0] > 500 && mother->args.R[1] > 500)
		mlx_put_image_to_window(mother->mlx.ptr,
			mother->mlx.win, mother->mlx.img_map.image, 0, 0);
}
