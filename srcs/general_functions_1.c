/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_functions_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 17:42:53 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/13 17:28:04 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	create_map(t_input *args)
{
	char	*dup;
	char *tmp;
	int		size;
	int		i;

	i = 0;
	while ((args->line)[i] == ' ' || (args->line)[i] == '1')
	{
		if (args->line[i] == '1')
		{
			size = ft_strlen(args->line);
			if (!(dup = malloc(sizeof(char) * (size + 2))))
				return;
			i = 0;
			while (i < size)
			{
				dup[i] = args->line[i];
				i++;
			}
			dup[i] = 'x';
			i++;
			dup[i] = '\0';
			tmp = ft_strjoin(args->map, dup);
			if (args->map)
				free(args->map);
			args->map = tmp;
			// free(tmp);
			// free(dup);
			break;
		}
		i++;
	}
}