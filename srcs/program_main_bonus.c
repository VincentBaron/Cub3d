/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_main_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:38:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/17 22:16:05 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error(t_general *mother, int e)
{
	if (e == 1 || e == 4 || e == 6 || e == 8 || e == 10)
	{
		if (mother->args.line)
			free(mother->args.line);
		if (mother->args.map)
			free(mother->args.map);
		if (e == 1)
			ft_putstr_fd("- Error 1: Map is unvalid -", 1);
		if (e == 6)
			ft_putstr_fd("- Error 6: Invalid texture -", 1);
		if (e == 10)
			ft_putstr_fd("- Error 5:duplicate or invalid element -", 1);
		if (e == 8)
			ft_putstr_fd("- Error 8: Invalid file -", 1);
	}
	if (e == 2)
		ft_putstr_fd("- Error 2: Arguments invalid -", 1);
	if (e == 3)
		ft_putstr_fd("- Error 3: Malloc Error -", 1);
	if (e == 5)
		ft_putstr_fd("- Error 5: Could not create bmp image -", 1);
	if (e != 2)
		ft_clean(mother);
	exit(1);
}

int	check_file(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (i < 4)
		return (0);
	i -= 3;
	if (ft_strncmp(&file[i], ".cub", 4) != 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_general	mother;

	if (argc != 2)
		error(&mother, 2);
	if (!check_file(argv[1]))
		error(&mother, 2);
	mother.args.fd = open(argv[1], __O_DIRECTORY);
	if (mother.args.fd != -1)
		error(&mother, 2);
	mother.args.fd = open(argv[1], O_RDONLY);
	if (mother.args.fd == -1)
		error(&mother, 2);
	init_vars(&mother);
	map_parsing(&(mother.args), &mother);
	init_map(&mother);
	position_info(&mother);
	game_start(&mother);
	return (0);
}
