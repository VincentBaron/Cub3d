/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:42:53 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/17 19:00:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_args_filled(t_general *mother)
{
	int	i;

	if (mother->args.c_filled + mother->args.r_filled
		+ mother->args.f_filled != 3)
		error(mother, 6);
	i = 0;
	while (i < 5)
	{
		if (mother->args.text[i].img_text.image == NULL)
			error(mother, 6);
		i++;
	}
}

void	build_str(t_general *mother, t_creator *creat)
{
	creat->size = ft_strlen(mother->args.line);
	creat->dup = malloc(sizeof(char) * (creat->size + 2));
	if (!(creat->dup))
		return ;
	creat->i = -1;
	while (++creat->i < creat->size)
		creat->dup[creat->i] = mother->args.line[creat->i];
	creat->dup[creat->i] = 'x';
	creat->i++;
	creat->dup[creat->i] = '\0';
	creat->tmp = ft_strjoin(mother->args.map, creat->dup);
	if (mother->args.map)
		free(mother->args.map);
	mother->args.map = ft_substr_bis(creat->tmp, 0, ft_strlen(creat->tmp));
	if (creat->tmp)
		free(creat->tmp);
	free(creat->dup);
}

void	create_map(t_general *mother)
{
	t_creator	creat;

	mother->map_started = 1;
	check_args_filled(mother);
	creat.i = 0;
	while (mother->args.line[creat.i])
	{
		if (check_charset(mother->args.line[creat.i], "012NSEW\n ") == -1)
			error(mother, 1);
		creat.i++;
	}
	creat.tmp = NULL;
	creat.i = 0;
	while ((mother->args.line)[creat.i] == ' '
		|| (mother->args.line)[creat.i] == '1')
	{
		if (mother->args.line[creat.i] == '1')
		{
			build_str(mother, &creat);
			break ;
		}
		creat.i++;
	}
}

int	is_empty_line(t_general *mother)
{
	int	i;

	i = 0;
	while (mother->args.line[i])
	{
		if (check_charset(mother->args.line[i], " \n") == -1)
			return (0);
		i++;
	}
	return (1);
}
