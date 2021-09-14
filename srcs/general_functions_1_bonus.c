/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:42:53 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/13 21:38:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void check_args_filled(t_general *mother)
{
	int i;

	if (mother->args.c_filled + mother->args.r_filled + mother->args.f_filled != 3)
		error(mother, 6);
	i = 0;
	while (i < 5)
	{
		if (mother->args.text[i].img_text.image == NULL)
			error(mother, 6);
		i++;
	}
}

void	create_map(t_general *mother)
{
	char	*dup;
	char *tmp;
	int		size;
	int		i;

	check_args_filled(mother);
	i = 0;
	while (mother->args.line[i])
	{
		if (check_charset(mother->args.line[i], "012NSEW\n ") == -1)
			error(mother, 1);
		i++;
	}
	tmp = NULL;
	i = 0;
	while ((mother->args.line)[i] == ' ' || (mother->args.line)[i] == '1')
	{
		if (mother->args.line[i] == '1')
		{
			size = ft_strlen(mother->args.line);
			if (!(dup = malloc(sizeof(char) * (size + 2))))
				return;
			i = 0;
			while (i < size)
			{
				dup[i] = mother->args.line[i];
				i++;
			}
			dup[i] = 'x';
			i++;
			dup[i] = '\0';
			tmp = ft_strjoin(mother->args.map, dup);
			if (mother->args.map)
				free(mother->args.map);
			mother->args.map = ft_substr_bis(tmp, 0, ft_strlen(tmp));
			if (tmp)
				free(tmp);
			free(dup);
			break;
		}
		i++;
	}
}