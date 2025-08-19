/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 18:00:57 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int32_t	main(int ac, char **av)
{
	t_projection	p;

	init_projection(&p);
	if (ac != 2)
		return (return_args_error());
	else
	{
		if (((check_file(av[1], ".fdf")) || (load_matrix(&p, av[1], 0, 1))))
			return (free_projection_return(&p));
	}
	set_matrix(&p);
	if (init_mlx(&p))
		return (free_projection_return(&p));
	mlx_scroll_hook(p.mlx, on_scroll, &p);
	mlx_loop_hook(p.mlx, ft_hook, &p);
	mlx_loop(p.mlx);
	if (p.image)
		mlx_delete_image(p.mlx, p.image);
	if (p.mlx)
		mlx_terminate(p.mlx);
	free_matrix(&p);
	return (EXIT_SUCCESS);
}

/*
TODO: Check return values
 */