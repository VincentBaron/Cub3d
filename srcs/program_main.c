/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <vbaron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:38:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/15 17:19:39 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    free_program(t_general *mother)
{
    int i;

    if (mother->args.matrix)
    {
        i = 0;
        while(mother->args.matrix[i++])
            ft_free(mother->args.matrix[i]);
    }
}

void    error(t_general *mother)
{
    if (mother->error == 1)
        ft_putstr_fd("- Error 1: Map is unvalid -", 1);
    if (mother->error == 2)
        ft_putstr_fd("- Error 2: Arguments invalid -", 1);
    if (mother->error == 3)
        ft_putstr_fd("- Error 3: Malloc Error -", 1);
    if (mother->error == 4)
        ft_putstr_fd("- Error 4: Too many players -", 1);
    //free_program(mother);
    exit(1);
}

/*void    save_image(t_general *mother)
{

}*/

int main(int argc, char **argv)
{
    t_general mother;

    if (argc < 2 || argc > 3)
    {
        mother.error = 2;
        error(&mother);
    }
    if ((mother.args.fd = open(argv[1], O_RDONLY)) == -1)
    {
        mother.error = 2;
        error(&mother);
    }
    //save_image(&mother);
    init_vars(&mother);
    map_parsing(&(mother.args), &mother);
    init_map(&mother);
    position_info(&mother);
    game_start(&mother);
    return (0);
}