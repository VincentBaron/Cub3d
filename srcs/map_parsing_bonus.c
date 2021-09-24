/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:02:56 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/17 19:06:27 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_spaces(t_general *mother, int i, int f)
{
	if (i - 1 < 0 || f - 1 < 0 || (f + 1
			== (int)ft_strlen(mother->args.matrix[i])))
		return (-1);
	if (check_charset(mother->args.matrix[i - 1][f], "012NSEW") == -1
		|| check_charset(mother->args.matrix[i + 1][f], "012NSEW") == -1
		|| check_charset(mother->args.matrix[i][f - 1], "012NSEW") == -1
		|| check_charset(mother->args.matrix[i][f + 1], "012NSEW") == -1)
		return (-1);
	return (0);
}

void	calculate_map_size(t_general *mother)
{
	int	i;
	int	f;
	int	player_number;

	mother->map.width = 0;
	mother->map.height = 0;
	player_number = 0;
	i = 0;
	while (mother->args.matrix[i])
	{
		f = 0;
		while (mother->args.matrix[i][f])
		{
			if (check_charset(mother->args.matrix[i][f], "NSEW") != -1)
				player_number++;
			f++;
		}
		if (f > mother->map.width)
			mother->map.width = f;
		i++;
	}
	if (player_number != 1)
		error(mother, 1);
}

void	check_map(t_general *mother)
{
	int	i;
	int	f;

	calculate_map_size(mother);
	i = 0;
	while (mother->args.matrix[i])
	{
		f = 0;
		while (mother->args.matrix[i][f])
		{
			if (mother->args.matrix[i][f] == '0')
				if (check_spaces(mother, i, f))
					error(mother, 1);
			f++;
		}
		i++;
	}
}

void	args_managment(t_general *mother, t_input *args)
{
	args->tracker = 0;
	while (args->line[args->tracker] == ' ')
		args->tracker++;
	if (!check_args(args))
		error(mother, 6);;
	args_definer(args, mother);
}

void	map_parsing(t_input *args, t_general *mother)
{
	int	res;

	mother->mlx.ptr = mlx_init();
	if (!mother->mlx.ptr)
		  error(mother, 6);
	(args->map) = ft_substr_bis("", 0, 0);
	initialise_args(args);
	res = get_next_line(args->fd, &(args->line));
	while (res != 0)
	{
		if (is_empty_line(mother) && mother->map_started)
			error(mother, 1);
		if (res == -1)
			error(mother, 8);
		if (!is_empty_line(mother) && mother->map_started == 0)
			args_managment(mother, args);
		if (args->index_i == 0)
			create_map(mother);
		ft_free(args->line);
		res = get_next_line(args->fd, &(args->line));
	}
	create_map(mother);
	args->matrix = ft_split(args->map, "x");
	check_map(mother);
	create_sprites(mother);
	ft_free(args->map);
	free(args->line);
}
