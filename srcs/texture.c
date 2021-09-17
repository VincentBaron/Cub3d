/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:38:29 by vincentbaro       #+#    #+#             */
/*   Updated: 2021/09/17 17:48:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_texture(t_input *args, t_general *mother)
{
	int	index;

	index = args->index_i - 2;
	if (args->text[index].img_text.image != NULL)
		error(mother, 10);
	args->text[index].path = ft_substr_bis(args->line, args->tracker,
			ft_strlen(args->line) - args->tracker);
	args->text[index].img_text.image = mlx_xpm_file_to_image(mother->mlx.ptr,
			args->text[index].path, &(args->text[index].text_width),
			&(args->text[index].text_height));
	if ((int)args->text[index].img_text.image == 0)
		error(mother, 6);
	args->text[index].img_text.addr = mlx_get_data_addr(args->text[index]
			.img_text.image, &(args->text[index].img_text.bpp),
			&(args->text[index].img_text.size_line),
			&(args->text[index].img_text.endian));
}

void	wall_position_calculation(t_general *mother)
{
	if (mother->dda.side_pos == 0)
		mother->map.wall_pos = mother->gps.pos.y + mother->dda.perpWallDist
			* mother->gps.ray.y;
	else
		mother->map.wall_pos = mother->gps.pos.x + mother->dda.perpWallDist
			* mother->gps.ray.x;
	mother->map.wall_pos -= floor(mother->map.wall_pos);
}

void	texture_calculation(t_general *mother, int text_index)
{
	mother->map.text_pos = (int)(mother->map.wall_pos
			* (double)(mother->args.text[text_index].text_width));
	if (mother->dda.side_pos == 0 && mother->gps.ray.x > 0)
		mother->map.text_pos = mother->args.text[text_index].text_width
			- mother->map.text_pos - 1;
	if (mother->dda.side_pos == 1 && mother->gps.ray.y < 0)
		mother->map.text_pos = mother->args.text[text_index].text_width
			- mother->map.text_pos - 1;
}
