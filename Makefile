# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sabrugie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/10 19:12:22 by sabrugie          #+#    #+#              #
#    Updated: 2020/09/10 14:26:19 by sabrugie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
HEADERS = includes

LIBFT_P = libft
MLX_P = minilibx

CC = gcc
CFLAGS = -Wall -Werror -Wextra $(OPTION)
OPTION = -I $(HEADERS) -I $(MLX_P) -I $(LIBFT_P)/includes

LDFLAGS = -L $(LIBFT_P) -lft -L $(MLX_P) -lmlx \
		  -framework OpenGL -framework AppKit -lm

CAM = $(addprefix camera/, camera.c)
ERROR = $(addprefix check_error/, check_error.c)
DEBUG = $(addprefix debug/, debug.c)
MATERIAL = $(addprefix material/, material.c scatter.c)
OBJECTS = $(addprefix objects/, hit.c objects.c plane.c sphere.c)
PARSE = $(addprefix parsing/, parser.c parsing_func1.c parsing_func2.c)
RAY = $(addprefix ray/, ray.c)
UTILS = $(addprefix utils/, skip_functions.c utils.c)
VEC = $(addprefix vector/, vector.c vector_operations1.c \
		vector_operations2.c)

SRCS =	$(addprefix srcs/, main.c $(CAM) $(ERROR) $(DEBUG) $(MATERIAL) $(OBJECTS) $(PARSE) $(RAY) $(UTILS) $(VEC))
		
#OBJS = $(SRCS:$(SRCS_P)%.c=$(OBJ_P)%.o)
OBJS = $(SRCS:.c=.o)
	

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_P) all
	make -C $(MLX_P) all
	$(CC) $(CFLAGS) -o ./$(NAME) $(OBJS) $(LDFLAGS)

clean:
	make -C $(LIBFT_P) clean
	make -C $(MLX_P) clean
	rm -rf $(OBJS)

anc: all clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT_P)/libft.a
	rm -rf $(MLX_P)/libmlx.a
re: fclean all
