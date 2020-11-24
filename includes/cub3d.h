/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincentbaron <vincentbaron@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:03:48 by vbaron            #+#    #+#             */
/*   Updated: 2020/11/06 09:48:54 by vincentbaro      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "stdlib.h"
# include <unistd.h>
# include "get_next_line.h"
# include "../Libft/libft.h"
# include "mlx.h"
# include "math.h"

//LINUX
/*
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define RIGHT_ARROW 65363
# define LEFT_ARROW 65361
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define UP 119
# define LEFT 97
# define DOWN 115
# define RIGHT 100
# define ESC 65307
*/

//MACOS

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define UP 13
# define LEFT 0
# define DOWN 1
# define RIGHT 2
# define ROT_RIGHT 124
# define ROT_LEFT 123

//MATHS

# define PI 3.141592

typedef struct s4_list
{
    int x;
    int y;
} t_coor;

typedef struct s_pix
{
    float x;
    float y;
} t_float;

typedef struct s1_list
{
    t_float pos;
    t_float dir;
    float square;
    int height;
    int width;
    t_float plane;
    t_float time;
    t_coor move;
    int rot_left;
    int rot_right;
    int event;
    float angle;
}   t_gps;

typedef struct s2_list
{
    int RGB[3];
    char *path;
} t_text;

typedef struct s3_list
{
    int         fd;
    char        *line;
    char        *map;
    char        **matrix;
    int         R[2];
    t_text      NO;
    t_text      SO;
    t_text      WE;
    t_text      EA;
    t_text      S;
    t_text      F;
    t_text      C;
    char        *index;
    int         index_i;
    int         tracker;
} t_input;

typedef struct s_img
{
    void *image;
    char *addr;
    int bpp;
    int endian;
    int size_line;
    unsigned int color;
} t_img;

typedef struct s12_list
{
    void *ptr;
    void *win;
    t_img img_map;
    t_img img_ray;
} t_mlx;

typedef struct s_map
{
    int size_x;
    int size_y;
    int track_x;
    int track_y;
} t_map;

typedef struct s_ray
{
    float dist_inter;
    t_float pos_inter;
    float angle;
    float dist_projection;
} t_ray;

typedef struct s5_list
{
    t_input args;
    t_mlx   mlx;
    t_gps   gps;
    t_map map;
    t_ray raycast;
}   t_general;

//map_parsing.c

void    error(void);
int     main(int argc, char **argv);
int     map_parsing(t_input *args);
int     check_charset(char c, char const *set);
void    args_definer(t_input *args);
int     **ft_realloc(int **tab);
void    splitter_alloc(t_input *args);
void    map_creator(t_input *args);

//general_functions_1.c

void	create_map(t_input *args);

//starting_info.c

void    position_info(t_general *mother);
void    find_direction(t_general *mother);

//mlx_functions.c

void    game_start(t_general *mother);
int events_list(t_general *mother);
int key_release(int keycode, t_general *mother);
int key_press(int keycode, t_general *mother);
char *draw_pixel(t_img *img, int x, int y);

//map_functions.c

void   pixel_color(t_general *mother, char *type);
void draw_square(t_general *mother, char *type);
void draw_player(t_general *mother);
void draw_map(t_general *mother);
void redefine_map(t_general *mother);
void  new_map(t_general *mother);
void redefine_position(t_general *mother);
int       check_angle(float angle, float a_max, float a_min);

//distance_calculations.c

char    check_collision(t_general *mother, t_float inter);
float   horizontal_intersection_calculation(t_general *mother);
float   vertical_intersection_calculation(t_general *mother);
void    check_intersection(t_general *mother);

//raycasting.c

void    set_texture(t_general *mother);
void    draw_slice(t_general *mother, float slice);
void    draw_rays(t_general *mother);
void draw_map_ray(t_general *mother);

#endif