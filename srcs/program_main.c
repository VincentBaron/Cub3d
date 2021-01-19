/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:38:34 by vbaron            #+#    #+#             */
/*   Updated: 2021/01/19 15:20:20 by vincentbaro      ###   ########.fr       */
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

void    error(t_general *mother, int e)
{
    (void)mother;
    if (e == 1)
        ft_putstr_fd("- Error 1: Map is unvalid -", 1);
    if (e == 2)
        ft_putstr_fd("- Error 2: Arguments invalid -", 1);
    if (e == 3)
        ft_putstr_fd("- Error 3: Malloc Error -", 1);
    if (e == 4)
        ft_putstr_fd("- Error 4: Too many players -", 1);
    if (e == 5)
        ft_putstr_fd("- Error 5: Could not create bmp image -", 1);
    
    //free_program(mother);
    exit(1);
}

/*void    save_image(t_general *mother)
{

}*/

int main(int argc, char **argv)
{
    t_general mother;

    mother.bmp.flag = 0;
    if (argc < 2 || argc > 3)
        error(&mother, 2);
    if (ft_strncmp(argv[1], "--save", 6) == 0)
        mother.bmp.flag = 1;
    if ((mother.args.fd = open(argv[mother.bmp.flag + 1], O_RDONLY)) == -1)
        error(&mother, 2);
    init_vars(&mother);
    map_parsing(&(mother.args), &mother);
    init_map(&mother);
    position_info(&mother);
    if (mother.bmp.flag == 1)
        save_image(&mother);
    else
        game_start(&mother);
    return (0);
}