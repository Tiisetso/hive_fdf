/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:31:18 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 20:19:29 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	init_coord(t_coord *coord, char **points, int x, int y)
{
	char	**coord_data;

	if (ft_strchr(points[x], ','))
	{
		coord_data = ft_split(points[x], ',');
		if (!coord_data)
			return (EXIT_FAILURE);
		if (assign_coord_z(coord, coord_data[0]))
		{
			free_split(coord_data);
			return (EXIT_FAILURE);
		}
		free_split(coord_data);
	}
	else
	{
		if (assign_coord_z(coord, points[x]))
			return (EXIT_FAILURE);
	}
	coord->x = x;
	coord->y = y;
	coord->rgba = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	return (EXIT_SUCCESS);
}

int	assign_coord_z(t_coord *coord, char *z_data)
{
	long	long_num;

	long_num = ft_atol(z_data);
	if ((long_num > 12000) || (long_num < -12000))
	{
		ft_printfd(2, "Only integers between -12000 and 12000 allowed.\n");
		return (EXIT_FAILURE);
	}
	else
		coord->z = (int)long_num;
	return (EXIT_SUCCESS);
}

int	set_points(t_projection *p, char **points, int y)
{
	int	i;

	i = 0;
	while (points[i])
		i++;
	if (y == 0)
		p->x_max = i;
	else
	{
		if (!(p->x_max == i))
		{
			ft_printfd(2, "Invalid map.\n");
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	inc_matrix(t_projection *p, int *cap, int fd, int y)
{
	t_coord	**temp;
	int		i;

	*cap = *cap + 1;
	temp = (t_coord **)malloc(sizeof(t_coord *) * *cap);
	if (!temp)
		return (free_matrix_return(p, y, fd, NULL));
	i = 0;
	while (i < y)
	{
		temp[i] = p->matrix[i];
		i++;
	}
	free(p->matrix);
	p->matrix = temp;
	return (EXIT_SUCCESS);
}

int	parse(t_projection *p, char *line, int y, int x)
{
	char	**points;
	t_coord	*coords;
	char	*trimmed_line;

	trimmed_line = ft_strtrim(line, " \n\t\v\r\f");
	if (!trimmed_line)
		return (EXIT_FAILURE);
	points = ft_split(trimmed_line, ' ');
	free(trimmed_line);
	if (!points)
		return (free_points_return(points));
	if (set_points(p, points, y))
		return (free_points_return(points));
	coords = (t_coord *)malloc(sizeof(t_coord) * (p->x_max));
	if (!coords)
		return (free_split_return(points));
	while (x < p->x_max)
	{
		if (init_coord(&coords[x], points, x, y))
			return (free_coords_points_return(points, coords));
		x++;
	}
	p->matrix[y] = coords;
	return (free_return_parse(points));
}
