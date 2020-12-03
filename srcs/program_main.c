/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 12:38:34 by vbaron            #+#    #+#             */
/*   Updated: 2020/12/03 16:56:31 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    error(void)
{
    write (1, "Error\n", 6);
}

/*void    save_image(t_general *mother)
{

}*/

int main(int argc, char **argv)
{
    t_general mother;

    if (argc < 2 || argc > 3)
      error();
    if ((mother.args.fd = open(argv[1], O_RDONLY)) == -1)
    {
        error();
        return (0);
    }
    //save_image(&mother);
    init_vars(&mother);
    map_parsing(&(mother.args));
    init_map(&mother);
    position_info(&mother);
    game_start(&mother);
    return (0);
}