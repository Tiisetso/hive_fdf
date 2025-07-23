/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 12:56:35 by timurray          #+#    #+#             */
/*   Updated: 2025/07/23 13:45:41 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>

typedef struct pnt {
	int x;
	int y;
	int z;
	int u;
	int v;
	int rgba;
} s_pnt;

#endif