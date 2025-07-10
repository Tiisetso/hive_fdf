# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/08 13:01:37 by timurray          #+#    #+#              #
#    Updated: 2025/07/08 13:36:25 by timurray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror

MLX42_DIR = MLX42/build
MLX_FLAGS = -Iinclude -ldl -lglfw -pthread -lm
MLX42 = $(MLX42_DIR)/libmlx42.a

SOURCES =	fdf.c

OBJECTS = $(SOURCES:.c=.o)

$(NAME): $(OBJECTS)
	$(CC) $(OBJECTS) $(MLX42) $(MLX_FLAGS) 

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re