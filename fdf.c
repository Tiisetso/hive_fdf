/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timurray <timurray@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:40:33 by timurray          #+#    #+#             */
/*   Updated: 2025/08/06 15:46:42 by timurray         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define WIDTH 1080
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

	rgba = 0xFFFFFF;
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



int32_t main(int ac, char **av)
{
	// mlx_t* mlx;
	char	*line;
	int 	fd;
	t_coord **matrix;
	t_coord **temp;
	int	x_count;
	int x;
	int y_count;
	int y;
	int i;

	x_count = 0;
	x = 0;
	y = 0;
	if (ac != 2)
		return (EXIT_FAILURE);
	else
	{
		matrix = (t_coord **)malloc(sizeof(t_coord *));
		y_count = 1;
		if (check_file(av[1], ".fdf"))
		{
			fd = open(av[1], O_RDONLY);
			while ((line = get_next_line(fd)))
			{
				matrix[y] = parse(line, y, &x);
				if(x < x_count)
					x = x_count;
				y++;
				if (y == y_count)
				{
					y_count++;
					temp = (t_coord **)malloc(sizeof(t_coord *) * y_count); //TODO: Memory
					i = 0;
					while (i < y)
					{
						temp[i] = matrix[i];
						i++;
					}
					free(matrix);
					matrix = temp;
				}
				
				ft_printf("%s", line);
				free(line);
			}	
		}
		else
			return (EXIT_FAILURE);
	}

	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "FDF", true)))
	// {
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (!(image = mlx_new_image(mlx, 1000, 1000)))
	// {
	// 	mlx_close_window(mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }
	// if (mlx_image_to_window(mlx, image, 10, 10) == -1)
	// {
	// 	mlx_close_window(mlx);
	// 	puts(mlx_strerror(mlx_errno));
	// 	return(EXIT_FAILURE);
	// }x
	
	// mlx_loop_hook(mlx, ft_randomize, mlx);
	// mlx_loop_hook(mlx, ft_put_grid, mlx);

	// mlx_loop_hook(mlx, ft_put_dots, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

/* 
TODO: Leaks, leaks, leaks. Correctly free.

TODO: Let's see those dots.
TODO: Transform array to isometric points.

TODO: Let's connect those dots.

TODO: colour?
TODO: atoi/atol?
TODO: zoom on scroll.

TODO: unsigned ints instead? Yeah come on.

TODO: Resize the window?
TODO: Colour transition
TODO: Orbit rotation?
 */