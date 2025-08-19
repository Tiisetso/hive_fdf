/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:27:46 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:45:11 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_hook(void *param)
{
	t_projection	*projection;
	mlx_t			*mlx;

	projection = param;
	mlx = projection->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	else
	{
		if (mlx_is_key_down(mlx, MLX_KEY_UP))
			projection->y_offset -= 5;
		if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
			projection->y_offset += 5;
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			projection->x_offset -= 5;
		if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
			projection->x_offset += 5;
		projection->redraw = 1;
	}
	if (projection->redraw)
	{
		render(projection);
		projection->redraw = 0;
	}
}

void	on_scroll(double dx, double dy, void *param)
{
	t_projection	*projection;
	int				new_gap;

	(void)dx;
	projection = param;
	new_gap = projection->gap + (int)dy;
	if (new_gap < 1)
		new_gap = 1;
	if (new_gap > 100)
		new_gap = 100;
	if (new_gap != projection->gap)
	{
		projection->gap = new_gap;
		projection->redraw = 1;
	}
}
