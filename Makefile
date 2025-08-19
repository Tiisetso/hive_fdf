# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 13:01:37 by timurray          #+#    #+#              #
#    Updated: 2025/08/19 17:39:14 by timurray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SOURCES = \
src/fdf.c src/isometric.c src/pixel.c \
src/hooks.c src/draw.c src/coord.c \
src/free_return.c src/initialize.c \
src/free_points_return.c src/free_matrix.c \
src/return_error.c 

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft/ -IMLX42/include
VFLAGS = -g
SFLAGS = -ggdb3 -fsanitize=address -fsanitize=leak -fsanitize=undefined

LIBFT_DIR  = ./libft
LIBFT = $(LIBFT_DIR)/libft.a 

MLX42_REPO = https://github.com/codam-coding-college/MLX42.git
MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build/libmlx42.a
MLX_FLAGS = -Iinclude -ldl -lglfw -pthread -lm

debug ?= 0

ifeq (${debug}, 1)
	CFLAGS := ${CFLAGS} ${VFLAGS}
endif
ifeq (${debug}, 2)
	CFLAGS := ${CFLAGS} ${SFLAGS}
endif

all: $(NAME)

$(NAME): $(MLX42_BUILD) $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX42_BUILD) $(MLX_FLAGS) -o $(NAME) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX42_DIR):
	git clone $(MLX42_REPO)

$(MLX42_BUILD): | $(MLX42_DIR)
	cmake -B $(MLX42_DIR)/build -S $(MLX42_DIR)
	cmake --build $(MLX42_DIR)/build -j4

clean:
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_DIR)
	rm -rf $(MLX42_DIR)/build

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

run: $(NAME)
	./$(NAME)

re: fclean all

.PHONY: all clean fclean re