# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 13:01:37 by timurray          #+#    #+#              #
#    Updated: 2025/08/02 13:14:10 by timurray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

SOURCES = \
fdf.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft/ -IMLX42/include

LIBFT_DIR  = ./libft
LIBFT = $(LIBFT_DIR)/libft.a 

MLX42_REPO  = https://github.com/codam-coding-college/MLX42.git
MLX42_DIR = MLX42
MLX42_BUILD = $(MLX42_DIR)/build/libmlx42.a
MLX_FLAGS = -Iinclude -ldl -lglfw -pthread -lm

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