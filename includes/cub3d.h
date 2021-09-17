/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:03:48 by vbaron            #+#    #+#             */
/*   Updated: 2021/09/17 18:19:43 by user42           ###   ########.fr       */
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
# include <fcntl.h>
# include <stdio.h>
# include <string.h>

//LINUX

# define KEY_PRESS 2
# define KEY_RELEASE 3
# define ROT_RIGHT 65363
# define ROT_LEFT 65361
# define UP 119
# define LEFT 97
# define DOWN 115
# define RIGHT 100
# define ESC 65307
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05


//MACOS

// # define KEY_PRESS 2
// # define KEY_RELEASE 3
// # define ESC 53
// # define UP 13
// # define LEFT 0
// # define DOWN 1
// # define RIGHT 2
// # define ROT_RIGHT 124
// # define ROT_LEFT 123
// # define MOVE_SPEED 0.1
// # define ROT_SPEED 0.05

//MATHS

# define PI 3.141592

typedef struct s_creator
{
    char	*dup;
	char	*tmp;
	int		size;
	int		i;
} t_creator;

typedef struct s4_list
{
    int x;
    int y;
} t_coor;

typedef struct s_pix
{
    double x;
    double y;
} t_double;

typedef struct s1_list
{
    t_double pos;
    t_double dir;
    t_double plane;
    t_coor move;
    int rot_left;
    int rot_right;
    int event;
    t_double camera;
    t_double ray;
}   t_gps;

typedef struct s_img
{
    void *image;
    char *addr;
    int bpp;
    int endian;
    int size_line;
    unsigned int color;
} t_img;

typedef struct sw_list
{
    char *path;
    int text_width;
    int text_height;
    t_img img_text;
} t_text;

typedef struct s2_list
{
    int RGB[3];
} t_rgb;

typedef struct s3_list
{
    int         fd;
    char        *line;
    char        *map;
    char        **matrix;
    int         R[2];
    int r_filled;
    int f_filled;
    int c_filled;
    t_text      text[5];
    t_rgb       F;
    t_rgb       C;
    int         index_i;
    char        *index[10];
    int         tracker;
    int textures;
} t_input;

typedef struct s12_list
{
    void *ptr;
    void *win;
    t_img img_map;
    t_img img_ray;
    t_img img_sprite;
    t_img text;
    int slice;
    int esc;
    int text_width;
    int text_height;
    int is_created;
} t_mlx;

typedef struct s_map
{
    int size_x;
    int size_y;
    int track_x;
    int track_y;
    int res_x;
    int res_y;
    double wall_pos;
    int text_pos;
    int width;
    int height;
} t_map;

typedef struct s_dda
{
    t_double side;
    t_coor map;
    t_double delta;
    t_coor step;
    double perpWallDist;
    int hit;
    int side_pos;
    int wall_height;
    int line_start;
    int line_end;
    int color;
}   t_dda;

typedef struct s_prite
{
    t_coor *elem;
    int *zbuffer;
    int sprite_count;
    int *sprite_order;
    int *sprite_distance;
    int spriteScreen;
    int sprite_height;
    t_coor draw_start;
    t_coor draw_end;
    int sprite_width;
    t_coor tex;
    t_double pos;
    t_double transform;
    int inv_det;
} t_sprite;

typedef struct s5_list
{
    t_input args;
    t_mlx   mlx;
    t_gps   gps;
    t_map map;
    t_dda dda;
    t_sprite sprite;
    int error;
    int map_started;
}   t_general;

//program_main.c

void    error(t_general *mother, int e);
int     main(int argc, char **argv);

//initialisation.c

void    init_vars(t_general *mother);
void    init_map(t_general *mother);
void    set_background(t_general *mother);

//map_parsing.c

void	map_parsing(t_input *args, t_general *mother);
void     args_definer(t_input *args, t_general *mother);
void    splitter_alloc(t_general *mother, t_input *args);
void    initialise_args(t_input *args);

// map_parsing2.c

int	fill_args(t_input *args, char **splitter);
void	splitter_alloc(t_general *mother, t_input *args);
void	args_definer(t_input *args, t_general *mother);
int	check_args(t_input *args);

//general_functions_1.c

void	create_map(t_general *mother);
int	is_empty_line(t_general *mother);

//starting_info.c

void    position_info(t_general *mother);
void    find_direction(t_general *mother);

//mlx_functions.c

void    game_start(t_general *mother);
int events_list(t_general *mother);
int key_release(int keycode, t_general *mother);
int key_press(int keycode, t_general *mother);
char *draw_pixel(t_img *img, int x, int y);
void movement_to_zero(t_general *mother);
void create_images(t_general *mother);
void display_images(t_general *mother);
int ft_clean(t_general *mother);


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

void    initial_side_distance(t_general *mother);
void    collision_calculator(t_general *mother);
void    distance_calculations(t_general *mother);

//raycasting.c

void    draw_wall(t_general *mother);
void    draw_line(t_general *mother);
void    raycasting(t_general *mother);
void    movement(t_general *mother);

//coloring.c

void    define_wall_color(t_general *mother);
void affiliate_texture(t_general *mother, t_img *img, t_text *texture);

//texture.c

void    define_texture_color(t_general *mother, int y);
void    wall_position_calculation(t_general *mother);
void    texture_calculation(t_general *mother, int text_index);
void    create_texture(t_input *args, t_general *mother);

//sprites.c

//static void    sprite_display(t_general *mother, int j, int stripe);
void    create_sprites(t_general *mother);
void    sort_sprites(t_general *mother);
void    sprite_projection(t_general *mother);
void    drawing_constrains(t_general *mother);


//bmp.c

void    fill_file(t_general *mother);
void save_image(t_general *mother);
void    create_header(t_general  *mother);
void    create_file(t_general *mother);



#endif