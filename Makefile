# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 13:01:37 by timurray          #+#    #+#              #
#    Updated: 2025/08/01 17:23:35 by timurray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf

CC = cc
CFLAGS = -Wall -Wextra -Werror -I libft/

LIBFT_DIR  = ./libft
LIBFT = $(LIBFT_DIR)/libft.a 

MLX42_DIR = MLX42/build
MLX_FLAGS = -Iinclude -ldl -lglfw -pthread -lm
MLX42 = $(MLX42_DIR)/libmlx42.a

SOURCES = \
fdf.c

OBJECTS = $(SOURCES:.c=.o)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT) $(MLX42) $(MLX_FLAGS) 

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: all clean fclean re