/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:33:29 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:45:45 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	free_return_parse(char **points)
{
	free_split(points);
	return (EXIT_SUCCESS);
}

int	free_split_return(char **points)
{
	free_split(points);
	return (EXIT_FAILURE);
}

int	free_projection_return(t_projection *p)
{
	free_matrix(p);
	return (EXIT_FAILURE);
}

int	free_coords_points_return(char **points, t_coord *coords)
{
	free(coords);
	free_split(points);
	return (EXIT_FAILURE);
}

int	close_fd_return(int fd)
{
	close(fd);
	return (EXIT_FAILURE);
}
