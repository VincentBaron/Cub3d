/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:02:56 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/10 20:30:38 by user42           ###   ########.fr       */
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
        if (mother->mlx.is_created == 0)
        {
            if (!(mother->mlx.win = mlx_new_window(mother->mlx.ptr, mother->args.R[0], mother->args.R[1], "J' aime les Moules Brite")))
                ft_putstr_fd("Error creating window", 2);
            mother->mlx.is_created = 1;
        }
       
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

int    check_spaces(t_general *mother, int i, int f)
{
    if ( i - 1 < 0 || f - 1 < 0 || (f + 1 == (int)ft_strlen(mother->args.matrix[i])))
        return (-1);

    if (check_charset(mother->args.matrix[i - 1][f], "012NSEW") == -1 || check_charset(mother->args.matrix[i + 1][f], "012NSEW") == -1 || check_charset(mother->args.matrix[i][f - 1], "012NSEW") == -1 || check_charset(mother->args.matrix[i][f + 1], "012NSEW") == -1)
        return(-1);
    return (0);
}

void     calculate_map_size(t_general *mother)
{
    int i;
    int f;
    int player_number;


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
        error(mother, 4);
}

void    check_map(t_general *mother)
{
    int i;
    int f;


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

int    map_parsing(t_input *args, t_general *mother)
{
    int res;
    
    if (!(mother->mlx.ptr = mlx_init()))
          ft_putstr_fd("Error initialising mlx", 2);
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
    check_map(mother);
    create_sprites(mother);
    ft_free(args->map);
    return (1);
}