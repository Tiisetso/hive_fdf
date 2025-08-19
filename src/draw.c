/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:29:10 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:30:04 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	line_low(mlx_image_t *img, t_coord start, t_coord end, int dy)
{
	int	yi;
	int	d;
	int	dx;

	dx = end.u - start.u;
	yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	while (start.u <= end.u)
	{
		put_pixel_safe(img, start.u, start.v, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF));
		if (d > 0)
		{
			start.v = start.v + yi;
			d = d + (2 * (dy - dx));
		}
		else
			d = d + (2 * dy);
		start.u++;
	}
}

void	line_high(mlx_image_t *img, t_coord start, t_coord end, int dx)
{
	int	xi;
	int	d;
	int	dy;

	dy = end.v - start.v;
	xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	while (start.v <= end.v)
	{
		put_pixel_safe(img, start.u, start.v, ft_pixel(0xFF, 0xFF, 0xFF, 0xFF));
		if (d > 0)
		{
			start.u = start.u + xi;
			d = d + (2 * (dx - dy));
		}
		else
			d = d + (2 * dx);
		start.v++;
	}
}

void	bresenham(mlx_image_t *img, t_coord start, t_coord end)
{
	int	dy;
	int	dx;

	dy = abs(end.v - start.v);
	dx = abs(end.u - start.u);
	if (dy < dx)
	{
		if (start.u > end.u)
			line_low(img, end, start, (start.v - end.v));
		else
			line_low(img, start, end, (end.v - start.v));
	}
	else
	{
		if (start.v > end.v)
			line_high(img, end, start, (start.u - end.u));
		else
			line_high(img, start, end, (end.u - start.u));
	}
}

void	ft_draw_line(t_projection *p)
{
	int	x;
	int	y;

	y = 0;
	while (y < p->y_max)
	{
		x = 0;
		while (x < p->x_max)
		{
			if ((y + 1) < p->y_max)
				bresenham(p->image, p->matrix[y][x], p->matrix[y + 1][x]);
			if ((x + 1) < p->x_max)
				bresenham(p->image, p->matrix[y][x], p->matrix[y][x + 1]);
			x++;
		}
		y++;
	}
}

void	render(t_projection *p)
{
	clear_image(p->image);
	isometric(p);
	ft_draw_line(p);
}
