/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:56:35 by timurray          #+#    #+#             */
/*   Updated: 2025/08/02 13:16:24 by timurray         ###   ########.fr       */
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
	int32_t rgba;
} t_coord;

#endif