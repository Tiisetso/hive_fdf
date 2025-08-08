/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/08 12:57:11 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 1920
#define HEIGHT 1920

static mlx_image_t* image;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

double rad(int deg)
{
	return (deg * 0.017453292519943295);
}

int iso_u(int alpha, double x, double y, double z)
{
	x = x * cos(rad(alpha));
	y = y * cos(rad(alpha + 120));
	z = z * cos(rad(alpha - 120));

	return ((int)round(x + y + z));
}

int iso_v(int alpha, double x, double y, double z)
{
	x = x * sin(rad(alpha));
	y = y * sin(rad(alpha + 120));
	z = z * sin(rad(alpha - 120));

	return ((int)round(x + y + z));
}

void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

int check_file(const char *filename, const char *extension)
{
	const char *dot;
	int ext_length;

	dot = ft_strrchr(filename, '.');
	ext_length = ft_strlen(extension);
	if (!dot || dot == filename)
		return (0);
	else
		return (ft_strncmp(dot, extension, ext_length) == 0);
}
t_coord *parse(char *line, int y, int *x_count)
{
	int		x;
	int		z;
	int32_t	rgba;
	char	**points;
	char	**colour_data;
	t_coord	*coords;

	rgba = 0xFFFFBB;
	points = ft_split(line, ' '); //TODO: check for failure
	x = 0;
	*x_count = 0;
	while (points[x++])
		(*x_count)++;
	coords = (t_coord *)malloc(sizeof(t_coord) * x);
	x = 0;
	while (x < *x_count)
	{
		if(ft_strchr(points[x], ','))
		{
			colour_data = ft_split(points[x], ',');
			z = ft_atoi(colour_data[0]);
			rgba = 0xFFFFFF; //TODO: Handle long for int32;
		}
		else
			z = ft_atoi(points[x]);
		coords[x].x = x;
		coords[x].y = y;
		coords[x].z = z;
		coords[x].rgba = rgba;
		x++;
	}
	//TODO: free points array.
	return (coords);
}

void line_low(int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int yi;
	int d;
	int y;
	int x;

	dx = x1 - x0;
	dy = y1 - y0;
	yi = 1;

	if(dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	d = (2 * dy) - dx;
	y = y0;

	x = x0;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	while (x < x1)
	{
		mlx_put_pixel(image, x, y, color);
		if (d > 0)
		{
			y = y + yi;
			d = d + (2 *(dy - dx));
		}
		else
		{
			d = d + (2*dy);
		}
		x++;
	}
}

void line_high(int x0, int y0, int x1, int y1)
{
	int dx;
	int dy;
	int xi;
	int d;
	int y;
	int x;

	dx = x1 - x0;
	dy = y1 - y0;
	xi = 1;

	if(dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	d = (2 * dx) - dy;
	x = x0;
	
	y = y0;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	while (y < y1)
	{
		mlx_put_pixel(image, x, y, color);
		if (d > 0)
		{
			x = x + xi;
			d = d + (2 *(dx - dy));
		}
		else
		{
			d = d + (2*dx);
		}
		y++;
	}
}

void bresenham(t_coord start, t_coord end)
{
	int dy;
	int dx;

	dy = abs(end.v - start.v);
	dx = abs(end.u - start.u);
	
	if (dy < dx)
	{
		if (start.u > end.u)
			line_low(end.u, end.v, start.u, start.v);
		else
			line_low(start.u, start.v, end.u, end.v);
	}
	else
	{
		if (start.v > end.v)
			line_high(end.u, end.v, start.u, start.v);
		else
			line_high(start.u, start.v, end.u, end.v);
	}
}

void ft_draw_line(t_coord **m, int max_x, int max_y)
{
	//loop through each point
	//put pixels if point is within bounds.
	(void)max_x;
	(void)max_y;
	bresenham(m[2][2], m[2][3]);
}

void ft_grid(t_coord **m, int max_x, int max_y)
{
	int x;
	int y;
	int gap;
	int alpha;
	uint32_t color = ft_pixel(0xFF, 0xFF, 0xFF, 0xFF);
	int x_offset = WIDTH / 2;
	int y_offset = HEIGHT / 2;
	
	y = 0;
	gap = 35;
	alpha = 30;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			m[y][x].u = iso_u(alpha, m[y][x].x*gap, m[y][x].y*gap, m[y][x].z*(gap)) + x_offset;
			m[y][x].v = iso_v(alpha, m[y][x].x*gap, m[y][x].y*gap, m[y][x].z*(gap)) + y_offset;
			mlx_put_pixel(image, m[y][x].u, m[y][x].v, color);
			
			x++;
		}
		y++;
	}
}

int32_t main(int ac, char **av)
{
	mlx_t* mlx;
	char	*line;
	int 	fd;
	t_coord **matrix;
	t_coord **temp;

	int	x_max;
	int y_max;
	int x;
	int y;
	int i;
	int cap;

	x_max = 0;
	y_max = 0;
	x = 0;
	y = 0;
	if (ac != 2)
		return (EXIT_FAILURE);
	else
	{
		if (check_file(av[1], ".fdf"))
		{
			fd = open(av[1], O_RDONLY);
			if(fd == -1)
			{
				ft_printf("File: %s not found.", av[1]);
				return (EXIT_FAILURE);
			}
			matrix = (t_coord **)malloc(sizeof(t_coord *));
			cap = 1;
			while ((line = get_next_line(fd)))
			{
				x = 0;
				matrix[y] = parse(line, y, &x);
				y++;
				if(x > x_max)
					x_max = x;
				if (y >= cap)
				{
					temp = (t_coord **)malloc(sizeof(t_coord *) * ++cap);
					if(!temp)
						return (EXIT_FAILURE);
					i = 0;
					while (i < y)
					{
						temp[i] = matrix[i];
						i++;
					}
					free(matrix);
					matrix = temp;
				}
				// ft_printf("%s", line); //TODO: Remove
				free(line);
			}
			y_max = y;
		}
		else
			return (EXIT_FAILURE);
	}

	if (!(mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}

	ft_grid(matrix, x_max, y_max);
	ft_draw_line(matrix, x_max, y_max);


	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

/* 
TODO: Leaks, leaks, leaks. Correctly free.

TODO: Let's connect those dots. to the right and down?

TODO: Image size to include all points. Drawing off to the left?

TODO: colour?
TODO: atoi/atol?
TODO: zoom on scroll.

TODO: unsigned ints instead?
TODO: Norminette.

TODO: Resize the window?
TODO: Colour transition
TODO: Orbit rotation?
 */