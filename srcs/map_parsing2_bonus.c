/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 21:41:59 by user42            #+#    #+#             */
/*   Updated: 2021/09/21 21:20:35 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_color(char **splitter)
{
	int	i;
	int	f;

	i = 0;
	while (splitter[i])
	{
		f = -1;
		while (splitter[i][++f])
		{
			if (splitter[i][f] > '9' || splitter[i][f] < '0')
				return (0);
		}
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	fill_args(t_input *args, char **splitter)
{
	int	x;
	int	err;

	x = 0;
	err = 0;
	if (!check_color(splitter))
		return (1);
	while (*splitter && x < 3)
	{
		if (ft_atoi(*splitter) < 0 || ft_atoi(*splitter) > 255
			|| ft_strlen(*splitter) > 3)
			err++;
		if (args->index_i == 7)
			args->f.rgb[x] = ft_atoi(*splitter);
		if (args->index_i == 8)
			args->c.rgb[x] = ft_atoi(*splitter);
		x++;
		splitter++;
	}
	if (args->index_i == 7)
		args->f_filled++;
	if (args->index_i == 8)
		args->c_filled++;
	return (err);
}

void	splitter_alloc(t_general *mother, t_input *args)
{
	char	**splitter;
	char	**head;
	int		x;
	int		err;

	err = 0;
	splitter = ft_split(&(args->line[args->tracker]), ",");
	head = splitter;
	if (args->index_i == 1)
		error(mother, 6);
	else
		err = fill_args(args, splitter);
	x = 0;
	while (head[x])
	{
		free(head[x]);
		x++;
	}
	free(head);
	if (err)
		error(mother, 6);
}

void	args_definer(t_input *args, t_general *mother)
{
	while (args->line[args->tracker] && !(args->line[args->tracker] >= '0'
			&& args->line[args->tracker] <= '9')
		&& args->line[args->tracker] != '.')
		args->tracker++;
	if (args->index_i != 0 && args->line[args->tracker - 1] != ' ')
		error(mother, 6);
	if (args->index_i >= 2 && args->index_i <= 6)
		create_texture(args, mother);
	if (args->index_i == 7 || args->index_i == 8 || args->index_i == 1)
		splitter_alloc(mother, args);
}

int	check_args(t_input *args)
{
	int	res;
	int	i;
	int	length;

	i = 0;
	if (args->line[args->tracker] == '1')
	{
		args->index_i = 0;
		return (1);
	}
	if (!check_dups(args->line))
		return (0);
	args->index_i = -1;
	while (args->index[++args->index_i])
	{
		length = i;
		if ((int)ft_strlen(args->index[args->index_i]) > i)
			length = (int)ft_strlen(args->index[args->index_i]);
		res = ft_strncmp(&(args->line[args->tracker]),
				args->index[args->index_i], length);
		if (res == 0)
			return (1);
	}
	return (0);
}
