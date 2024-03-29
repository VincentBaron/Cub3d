# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/24 17:36:15 by vbaron            #+#    #+#              #
#    Updated: 2021/09/17 21:38:45 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DIR_S = srcs
DIR_B = bonus
DIR_O = objs

SOURCES = general_functions_1_bonus.c \
		map_parsing_bonus.c \
		map_parsing2_bonus.c \
		program_main_bonus.c \
		starting_info_bonus.c \
		mlx_functions_bonus.c \
		mlx_functions2_bonus.c \
		get_next_line_bonus.c \
		get_next_line_utils_bonus.c \
		map_functions_bonus.c \
		raycasting_bonus.c \
		distance_calculations_bonus.c \
		initialisation_bonus.c \
		texture_bonus.c \
		sprites_bonus.c \
		sprites2_bonus.c \
		movement_bonus.c \

SRCS = $(addprefix $(DIR_S)/,$(SOURCES))
OBJS = $(addprefix $(DIR_O)/,$(SOURCES:.c=.o))

HEADERS = headers
LIBFT_DIR = Libft

######################################################
##DIR_MacOS
# MLX_DIR = mlx-macos
######################################################
##DIR_Linux
MLX_DIR = mlx-linux
#######################################################

NAME = cub3D

########################################################
##MacOs
#CC = gcc
########################################################
##Linux
CC = clang
########################################################

CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

########################################################
##MacOS
#-I /usr/X11/include -g -L /usr/X11/lib -lX11 -lmlx -lXext 
# LIBS = -framework OpenGL -framework Appkit
########################################################
##Linux
LIBS = -lXext -lX11 -lm
########################################################

MLX = $(addprefix $(MLX_DIR)/,libmlx.a)

LIBFT = $(addprefix $(LIBFT_DIR)/,libft.a)

all: $(LIBFT) $(MLX) $(NAME)

$(DIR_O)/%.o: $(DIR_S)/%.c
	mkdir -p $(DIR_O)	
	$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS) $(LIBFT) $(MLX)
		$(CC) $(CFLAGS) $(LIBS) $^ -o $@

bonus: all

$(LIBFT):
		 make -C $(LIBFT_DIR)

$(MLX):
		 make -C $(MLX_DIR)

clean:
		rm -f $(OBJS)		
	rm -f $(OBJS)/*.o
	rm -rf $(DIR_O)	
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

re: fclean all

.PHONY: re fclean all clean
