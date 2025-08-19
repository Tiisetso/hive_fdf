/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:35:45 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:45:55 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_matrix(t_projection *p)
{
	int	y;

	if (!p || (!p->matrix))
		return ;
	y = 0;
	while (y < p->y_max)
	{
		free(p->matrix[y]);
		y++;
	}
	free(p->matrix);
	p->matrix = NULL;
	p->x_max = 0;
	p->y_max = 0;
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	load_matrix_return(t_projection *p, int y, int fd)
{
	close(fd);
	p->y_max = y;
	if (y > 0)
		return (EXIT_SUCCESS);
	else
	{
		free(p->matrix);
		p->matrix = NULL;
		return (EXIT_FAILURE);
	}
}

int	free_matrix_return(t_projection *p, int y, int fd, char *line)
{
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	p->y_max = y;
	free_matrix(p);
	close(fd);
	return (EXIT_FAILURE);
}

int	free_matrix_fd_return(t_projection *p, int fd)
{
	free(p->matrix);
	p->matrix = NULL;
	close(fd);
	return (EXIT_FAILURE);
}
