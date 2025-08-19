/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:37:52 by timurray          #+#    #+#             */
/*   Updated: 2025/08/19 15:46:14 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	load_matrix(t_projection *p, char *file, int y, int cap)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (EXIT_FAILURE);
	p->matrix = (t_coord **)malloc(sizeof(t_coord *));
	if (!p->matrix)
		return (close_fd_return(fd));
	line = get_next_line(fd);
	if (!line)
		return (free_matrix_fd_return(p, fd));
	while (line)
	{
		if (parse(p, line, y, 0))
			return (free_matrix_return(p, y, fd, line));
		free(line);
		if (++y >= cap)
		{
			if (inc_matrix(p, &cap, fd, y))
				return (EXIT_FAILURE);
		}
		line = get_next_line(fd);
	}
	return (load_matrix_return(p, y, fd));
}

int	check_file(const char *filename, const char *ext)
{
	const char	*dot;
	int			ext_len;

	dot = ft_strrchr(filename, '.');
	ext_len = ft_strlen(ext);
	if ((!dot || dot == filename))
		return (EXIT_FAILURE);
	else
		return (!((ft_strncmp(dot, ext, ext_len) == 0)
				&& dot[ext_len] == '\0'));
}

void	init_projection(t_projection *p)
{
	p->x_max = 0;
	p->y_max = 0;
	p->gap = 1;
	p->x_offset = 0;
	p->y_offset = 0;
	p->redraw = 1;
	p->mlx = NULL;
	p->image = NULL;
	p->matrix = NULL;
	p->alpha = 30;
	p->height = 1920;
	p->width = 1920;
}

int	init_mlx(t_projection *p)
{
	p->mlx = mlx_init(p->width, p->height, "FDF", true);
	if (!(p->mlx))
	{
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	p->image = mlx_new_image(p->mlx, p->width, p->height);
	if (!(p->image))
	{
		mlx_close_window(p->mlx);
		mlx_terminate(p->mlx);
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	if (mlx_image_to_window(p->mlx, p->image, 0, 0) == -1)
	{
		mlx_delete_image(p->mlx, p->image);
		mlx_close_window(p->mlx);
		mlx_terminate(p->mlx);
		ft_printf("%s\n", mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

void	set_matrix(t_projection *p)
{
	p->gap = (int)round(p->height / p->x_max / 3);
	p->y_offset = p->height / 2;
	p->x_offset = p->width / 2;
}
