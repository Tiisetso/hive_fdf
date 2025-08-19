/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:08:06 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:13:31 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

double	rad(int deg)
{
	return (deg * 0.017453292519943295);
}

int	iso_u(int alpha, double x, double y, double z)
{
	x = x * cos(rad(alpha));
	y = y * cos(rad(alpha + 120));
	z = z * cos(rad(alpha - 120));
	return ((int)round(x + y + z));
}

int	iso_v(int alpha, double x, double y, double z)
{
	x = x * sin(rad(alpha));
	y = y * sin(rad(alpha + 120));
	z = z * sin(rad(alpha - 120));
	return ((int)round(x + y + z));
}

void	isometric(t_projection *p)
{
	int		x;
	int		y;
	t_coord	*c;

	y = 0;
	while (y < p->y_max)
	{
		x = 0;
		while (x < p->x_max)
		{
			c = &p->matrix[y][x];
			c->u = iso_u(p->alpha, c->x * p->gap, c->y * p->gap, c->z * p->gap)
				+ p->x_offset;
			c->v = iso_v(p->alpha, c->x * p->gap, c->y * p->gap, c->z * p->gap)
				+ p->y_offset;
			x++;
		}
		y++;
	}
}
