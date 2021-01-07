/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:02:56 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/07 15:31:37 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    initialise_args(t_input *args)
{
    args->index[0] = "1";
    args->index[1] = "R";
    args->index[2] = "NO";
    args->index[3] = "SO";
    args->index[4] = "WE";
    args->index[5] = "EA";
    args->index[6] = "S";
    args->index[7] = "F";
    args->index[8] = "C";
    args->index[9] = NULL;

    args->F.RGB[0] = -1;
    args->C.RGB[0] = -1;
}

void    splitter_alloc(t_input *args)
{
    char **splitter;
    int x;

    x = 0;
    splitter = ft_split(&(args->line[args->tracker]), ", ");
    if (args->index_i == 1)
    {
        args->R[0] = ft_atoi(splitter[0]);
        args->R[1] = ft_atoi(splitter[1]);
    }
    else
    {
        while (*splitter && x < 3)
        {
            if (args->index_i == 7)
                args->F.RGB[x] = ft_atoi(*splitter);
            if (args->index_i == 8)
                args->C.RGB[x] = ft_atoi(*splitter);
            x++;
            splitter++;
        }
    }
}

void     args_definer(t_input *args, t_general *mother)
{       
        while (args->line[args->tracker] && !(args->line[args->tracker] >= '0' && args->line[args->tracker] <= '9') && args->line[args->tracker] != '.')
            args->tracker++;
        if (args->index_i >= 2 && args->index_i <= 6)
            create_texture(args, mother);
        if (args->index_i == 7 || args->index_i == 8 || args->index_i == 1)
            splitter_alloc(args);
        if (!(mother->mlx.ptr = mlx_init()))
          ft_putstr_fd("Error initialising mlx", 2);
        if (!(mother->mlx.win = mlx_new_window(mother->mlx.ptr, mother->args.R[0], mother->args.R[1], "J' aime les Moules Brite")))
          ft_putstr_fd("Error creating window", 2);
}

int    check_args(t_input *args)
{
        int res;

        args->index_i = 0;
        while(args->index[args->index_i])
        {
            if ((res = ft_strncmp(&(args->line[args->tracker]), args->index[args->index_i], ft_strlen(args->index[args->index_i])) == 0))
                break;
            args->index_i++;
        }
        return (res);

}

int    map_parsing(t_input *args, t_general *mother)
{
    int res;
    
    (args->map) = ft_strdup("");
   initialise_args(args);
    while ((res = get_next_line(args->fd, &(args->line))) != 0)
    {
        if (res == -1)
            return (-1);
        args->tracker = 0;
        while (args->line[args->tracker] == ' ')
            args->tracker++;
        check_args(args);
        if (args->index_i == 0)
            create_map(args);
        else if (args->index_i > 0)
            args_definer(args, mother);
        ft_free(args->line);
    }
    create_map(args);
    args->matrix = ft_split(args->map, "x");
    create_sprites(mother);
    ft_free(args->map);
    return (1);
}