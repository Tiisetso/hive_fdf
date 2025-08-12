/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:56:35 by timurray          #+#    #+#             */
/*   Updated: 2025/08/12 13:32:15 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "MLX42/MLX42.h"
# include <math.h>
# include "libft.h"
# include <fcntl.h> 

typedef struct s_coord {
	int x;
	int y;
	int z;
	int u;
	int v;
	uint32_t rgba;
} t_coord;

typedef struct s_projection {
	mlx_t *mlx;
	mlx_image_t *image;
	t_coord	**matrix;
	int x_max;
	int y_max;
	int gap;
	int alpha;
	int x_offset;
	int y_offset;
	int redraw;
} t_projection;

void render(t_projection *projection);

#endif